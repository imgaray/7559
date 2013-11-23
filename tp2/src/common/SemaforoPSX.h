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


class SemaforoPSX {
public:
	SemaforoPSX(const char* nombre,  int valorInicial = 0);

	void wait();

	void signal();

	void destruir();

	virtual ~SemaforoPSX();
private:
	std::string _nombre;
	sem_t *_semaforo;
};

#endif /* SEMAFOROPSX_H_ */