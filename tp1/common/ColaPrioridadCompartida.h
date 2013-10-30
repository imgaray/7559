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
#include "MemoriaCompartida.h"

class ColaPrioridadCompartida {
public:
	ColaPrioridadCompartida();
	virtual ~ColaPrioridadCompartida();
	void inicializar();
	void push(Avion& avion);
	Avion pop();
	void cerrar();
private:
	struct ElementosCompartidos {
		EstrategiaAvion memoria[33];
		char index;
		bool abierta;
	};
	static char const* rutaMemoria;
	Semaforo semaforoPush;
	Semaforo semaforoPop;
	LockFile lock;
	MemoriaCompartida<struct ElementosCompartidos> memoria;
};

#endif /* COLAPRIORIDADCOMPARTIDA_H_ */
