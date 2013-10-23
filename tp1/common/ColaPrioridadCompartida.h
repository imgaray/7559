/*
 * ColaPrioridadCompartida.h
 *
 *  Created on: Oct 22, 2013
 *      Author: nacho
 */

#ifndef COLAPRIORIDADCOMPARTIDA_H_
#define COLAPRIORIDADCOMPARTIDA_H_
#include "Semaforo.h"
#include "Avion.h"
#include "LockFile.h"

class ColaPrioridadCompartida {
public:
	ColaPrioridadCompartida();
	virtual ~ColaPrioridadCompartida();
	void push(Avion& avion);
	Avion pop();
	void cerrar();
private:
	Semaforo semaforoPush;
	Semaforo semaforoPop;
	LockFile lock;
	Avion memoria[33];
	char index;
	bool abierta;
};

#endif /* COLAPRIORIDADCOMPARTIDA_H_ */
