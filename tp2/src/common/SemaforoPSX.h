/*
 * SemaforoPSX.h
 *
 *  Created on: 22/11/2013
 *      Author: migue
 */

#ifndef SEMAFOROPSX_H_
#define SEMAFOROPSX_H_

#include <string>
#include <semaphore.h>

#include "Semaforo.h"

/**
 * Clase "Adpater" de Semaforo
 */

class SemaforoPSX {
public:
	SemaforoPSX(const char* nombre,  int valorInicial = 0);

	void inicializar();

	void wait();

	void signal();

	void destruir();

	int valorActual();

	virtual ~SemaforoPSX();
private:
	std::string _nombre;
	Semaforo *_semaforo;
};

#endif /* SEMAFOROPSX_H_ */
