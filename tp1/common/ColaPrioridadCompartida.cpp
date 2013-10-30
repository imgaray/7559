/*
 * ColaPrioridadCompartida.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: nacho
 */

#include "ColaPrioridadCompartida.h"
#include "Logger.h"

char const* ColaPrioridadCompartida::rutaMemoria = "/tmp/cola_prioridad_elementos";

#define TAG "ColaPrioridad"

void swap(EstrategiaAvion* a, EstrategiaAvion* b) {
	EstrategiaAvion aux = *a;
	*a = *b;
	*b = aux;
}

ColaPrioridadCompartida::ColaPrioridadCompartida():
	semaforoPush("/tmp/semaforo_push_cola_prioridad", 32),
	semaforoPop("/tmp/semaforo_pop_cola_prioridad", 0),
	//lock("/tmp/lock_cola_prioridad"),
	lock(rutaMemoria),
	memoria(rutaMemoria, 'a'){
	/*struct ElementosCompartidos elementos;
	for (int i = 0; i < 33; i++) {
		elementos.memoria[i] = INEXISTENTE;
	}
	elementos.abierta = true;
	elementos.index = 1;
	memoria.escribir(elementos);
	Logger::instance().info(TAG, "creacion exitosa");*/
}

ColaPrioridadCompartida::~ColaPrioridadCompartida() {
	memoria.liberar();
	semaforoPop.eliminar();
	semaforoPush.eliminar();
}

void ColaPrioridadCompartida::inicializar(){
	struct ElementosCompartidos elementos;
	for (int i = 0; i < 33; i++) {
		elementos.memoria[i] = INEXISTENTE;
	}
	semaforoPush.inicializar();
	semaforoPop.inicializar();
	elementos.abierta = true;
	elementos.index = 1;
	memoria.escribir(elementos);
	Logger::instance().info(TAG, "creacion exitosa");
}

void ColaPrioridadCompartida::push(Avion& avion) {
	struct ElementosCompartidos elementos = memoria.leer();
	Logger::instance().info(TAG, "ingresando al push");
	if (!elementos.abierta)
		throw "cerrada la cola";
	semaforoPush.p();
	elementos = memoria.leer();
	lock.tomarLock();
	if (!elementos.abierta) {
		lock.liberarLock();
		throw "cerrada la cola";
	}
	elementos.memoria[elementos.index] = avion.getEstrategia();
	char pos = elementos.index++;
	while(pos > 1 && elementos.memoria[pos/2] < elementos.memoria[pos])
	{
		swap(&elementos.memoria[pos/2], &elementos.memoria[pos]);
		pos /= 2;
	}
	memoria.escribir(elementos);
	lock.liberarLock();
	semaforoPop.v();
	Logger::instance().info(TAG, "saliendo del push");
}

Avion ColaPrioridadCompartida::pop() {
	struct ElementosCompartidos elementos = memoria.leer();
	Logger::instance().info(TAG, "ingresando al pop");
	if (elementos.index == 1 && !elementos.abierta)
		throw "cerrada la cola";
	semaforoPop.p();
	elementos = memoria.leer();
	lock.tomarLock();
	if (elementos.index == 1 && !elementos.abierta) {
		lock.liberarLock();
		semaforoPop.v(); 
		throw "cerrada la cola";
	}
	Avion aux (elementos.memoria[1]);
	if (aux.determinarPrioridad() < TIERRA) {
		elementos.abierta = false;
		memoria.escribir(elementos);
		semaforoPop.v();
		lock.liberarLock();
		throw "cerrada la cola";
	}
	const char* mierda = aux.serializar();
	delete[] mierda;
	elementos.memoria[1] = elementos.memoria[--elementos.index];
	char pos = 1;
	while (2 * pos < elementos.index) {
		char pos1 = 2*pos;
		char pos2 = 2*pos + 1;
		char posaux = pos1;
		if (pos2 < elementos.index) {
			posaux = elementos.memoria[pos1] < elementos.memoria[pos2]? pos2 : pos1;
		}
		if (elementos.memoria[posaux] < elementos.memoria[pos])
			break;
		swap(&elementos.memoria[posaux], &elementos.memoria[pos]);
		pos = posaux;
	}
	memoria.escribir(elementos);
	lock.liberarLock();
	semaforoPush.v();
	const char* serial = aux.serializar();
	Logger::instance().info(TAG, "terminado el pop, devolviendo " + std::string(serial));
	delete[] serial;
	return aux;
}

void ColaPrioridadCompartida::cerrar() {
	lock.tomarLock();
	struct ElementosCompartidos elem = memoria.leer();
	elem.abierta = false;
	memoria.escribir(elem);
	lock.liberarLock();
	semaforoPop.v();
	semaforoPush.v();
}

