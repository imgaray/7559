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
	lock("/tmp/lock_cola_prioridad"),
	memoria(rutaMemoria, 'a'){
	struct ElementosCompartidos elementos;
	for (int i = 0; i < 33; i++) {
		elementos.memoria[i] = INEXISTENTE;
	}
	elementos.abierta = true;
	elementos.index = 1;
	memoria.escribir(elementos);
	Logger::instance().info(TAG, "creacion exitosa");
}

ColaPrioridadCompartida::~ColaPrioridadCompartida() {

}

void ColaPrioridadCompartida::push(Avion& avion) {
	struct ElementosCompartidos elementos = memoria.leer();
	Logger::instance().debug(TAG, "por ingresar al push");
	if (!elementos.abierta)
		throw "cerrada la cola";
	semaforoPush.p();
	Logger::instance().debug(TAG, "pasando el semaforo push");
	const char* mierda = avion.serializar();
	Logger::instance().debug(TAG, "ingresando un avion " + std::string(mierda));
	delete[] mierda;
	elementos = memoria.leer();
	lock.tomarLock();
	if (!elementos.abierta) {
		lock.liberarLock();
		throw "cerrada la cola";
	}
	Logger::instance().debug(TAG, "tomado el lock de la estructura");
	elementos.memoria[elementos.index] = avion.getEstrategia();
	char pos = elementos.index++;
	while(pos > 0 && elementos.memoria[pos/2] < elementos.memoria[pos])
	{
		swap(&elementos.memoria[pos/2], &elementos.memoria[pos]);
		pos /= 2;
	}
	Logger::instance().debug(TAG, "terminada la operacion de heap");
	memoria.escribir(elementos);
	lock.liberarLock();
	semaforoPop.v();
	Logger::instance().debug(TAG, "terminado el push");
}

Avion ColaPrioridadCompartida::pop() {
	struct ElementosCompartidos elementos = memoria.leer();
	Logger::instance().info(TAG, "ingresando al pop");
	if (elementos.index == 1 && !elementos.abierta)
		throw "cerrada la cola";
	semaforoPop.p();
	Logger::instance().info(TAG, "pasado el semaforo de pop");
	elementos = memoria.leer();
	lock.tomarLock();
	Logger::instance().info(TAG, "tomado el lock estructural en pop");
	if (elementos.index == 1 && !elementos.abierta) {
		lock.liberarLock();
		throw "cerrada la cola";
	}
	Avion aux (elementos.memoria[1]);
	if (aux.determinarPrioridad() < TIERRA) {
		lock.liberarLock();
		throw "cerrada la cola";
	}
	const char* mierda = aux.serializar();
	Logger::instance().info(TAG, "sacando el avion " + std::string(mierda));
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
	Logger::instance().info(TAG, "terminada operacion de heap");
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

