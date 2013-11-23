/*
 * SemaforoPSX.cpp
 *
 *  Created on: 22/11/2013
 *      Author: migue
 */

#include "SemaforoPSX.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

SemaforoPSX::SemaforoPSX(const char* nombre, int valorInicial) {
	_semaforo = NULL;

	if (nombre != NULL) {
		_nombre = nombre;
		_semaforo = sem_open(_nombre.c_str(), O_CREAT, 0664, valorInicial);

		if (_semaforo == SEM_FAILED) {
			std::string msj = "Error al crear semaforo: ";
			msj += _nombre;
			msj += std::string(strerror(errno));

			throw msj;
		}
	}
}

void SemaforoPSX::wait() {
	if (_semaforo == NULL) {
		std::string msj = "Error al hacer wait, semaforo no creado: ";
		msj += _nombre;
		throw msj;
	}
	else {
		sem_wait(_semaforo);
	}
}

void SemaforoPSX::signal() {
	if (_semaforo == NULL) {
		std::string msj = "Error al hacer signal, semaforo no creado: ";
		msj += _nombre;
		throw msj;
	}
	else {
		sem_post(_semaforo);
	}
}

void SemaforoPSX::destruir() {
	if (_semaforo != NULL) {
		sem_close(_semaforo);
		sem_unlink(_nombre.c_str());
		_semaforo = NULL;
	}
}

SemaforoPSX::~SemaforoPSX() {
	if (_semaforo != NULL) {
		sem_close(_semaforo);
	}
}
