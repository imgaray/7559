/*
 * ColaPrioridadCompartida.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: nacho
 */

#include "ColaPrioridadCompartida.h"

char const* ColaPrioridadCompartida::rutaMemoria = "/tmp/cola_prioridad_elementos";

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
}

ColaPrioridadCompartida::~ColaPrioridadCompartida() {

}

void ColaPrioridadCompartida::push(Avion& avion) {
	struct ElementosCompartidos elementos = memoria.leer();
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
	while(pos > 0 && elementos.memoria[pos/2] < elementos.memoria[pos])
	{
		swap(&elementos.memoria[pos/2], &elementos.memoria[pos]);
		pos /= 2;
	}
	memoria.escribir(elementos);
	lock.liberarLock();
	semaforoPop.v();
}

Avion ColaPrioridadCompartida::pop() {
	struct ElementosCompartidos elementos = memoria.leer();
	if (!elementos.abierta)
		throw "cerrada la cola";
	semaforoPop.p();
	elementos = memoria.leer();
	lock.tomarLock();
	if (!elementos.abierta) {
		lock.liberarLock();
		throw "cerrada la cola";
	}
	Avion aux (elementos.memoria[1]);
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
	return aux;
}

void ColaPrioridadCompartida::cerrar() {
	struct ElementosCompartidos elem = memoria.leer();

	semaforoPop.v();
	semaforoPush.v();
}

