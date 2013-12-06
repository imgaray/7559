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
#include <string>
#include <string.h>

SemaforoPSX::SemaforoPSX(const char* nombre, int valorInicial) {
	_semaforo = NULL;

	if (nombre != NULL) {
		_nombre = nombre;
		_semaforo = new Semaforo(_nombre, valorInicial);
	}
	else {
		std::string msj = "Instanciado semaforo desde PATH NULL";
		throw msj;
	}
}

void SemaforoPSX::wait() {
	if (_semaforo == NULL) {
		std::string msj = "Error al hacer wait, semaforo no creado: ";
		msj += _nombre;
		throw msj;
	}
	else {
		this->_semaforo->p();
	}
}

void SemaforoPSX::signal() {
	if (_semaforo == NULL) {
		std::string msj = "Error al hacer signal, semaforo no creado: ";
		msj += _nombre;
		throw msj;
	}
	else {
		this->_semaforo->v();
	}
}

void SemaforoPSX::inicializar() {
	_semaforo->inicializar();
}

void SemaforoPSX::destruir() {
	if (_semaforo != NULL) {
		_semaforo->eliminar();
		delete _semaforo;
		_semaforo = NULL;
	}
}


int SemaforoPSX::valorActual() {
	return _semaforo->valorActual();
}

SemaforoPSX::~SemaforoPSX() {
	if (_semaforo != NULL) {
		delete _semaforo;
	}
}

