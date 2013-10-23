/*
 * ColaPrioridadCompartida.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: nacho
 */

#include "ColaPrioridadCompartida.h"

ColaPrioridadCompartida::ColaPrioridadCompartida():
	semaforoPush("/tmp/semaforo_push_cola_prioridad", 32),
	semaforoPop("/tmp/semaforo_pop_cola_prioridad", 0),
	lock("/tmp/lock_cola_prioridad"),
	index(1),
	abierta(1){
}

ColaPrioridadCompartida::~ColaPrioridadCompartida() {
}

void ColaPrioridadCompartida::push(Avion& avion) {
	if (!abierta)
		throw "cerrada la cola";
	semaforoPush.p();
	if (!abierta)
		throw "cerrada la cola";
	lock.tomarLock();
	memoria[index] = avion;
	char pos = index++;
	while(pos > 0 && memoria[pos/2] < memoria[pos])
	{
		memoria[pos/2] < memoria[pos];
		pos /= 2;
	}
	semaforoPop.v();
	lock.liberarLock();
}

Avion ColaPrioridadCompartida::pop() {
	if (!abierta)
		throw "cerrada la cola";
	semaforoPop.p();
	if (!abierta)
		throw "cerrada la cola";

	lock.tomarLock();
	Avion aux = memoria[0];
	memoria[1] = memoria[index--];
	char pos = 1;
	while (2 * pos < index) {
		char pos1 = 2*pos;
		char pos2 = 2*pos + 1;
		char posaux = pos1;
		if (pos2 < index) {
			posaux = memoria[pos1] < memoria[pos2]? pos2 : pos1;
		}
		if (memoria[posaux] < memoria[pos])
			break;
		Avion aux = memoria[posaux];
		memoria[posaux] = memoria[pos];
		memoria[pos] = aux;
		pos = posaux;
	}
	semaforoPush.v();
	lock.liberarLock();
	return aux;
}

void ColaPrioridadCompartida::cerrar() {
	abierta = false;
	semaforoPop.v();
	semaforoPush.v();
}

