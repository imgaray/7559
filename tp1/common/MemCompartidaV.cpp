/*
 * MemoriaCompartida.cpp
 *
 *  Created on: 25/10/2013
 *      Author: migue
 */


#include "MemCompartidaV.h"
#include <sys/ipc.h>
#include <sys/shm.h>

#include <string>
#include <errno.h>
#include <string.h>

MemCompartidaV::MemCompartidaV(const std::string rutaArchivo, char id) :
	_rutaArch(rutaArchivo) {
	_creado = false;
	_liberada = false;
	_datos = NULL;
	_idArch = id;
	_tamMemoria = 0;
}


int MemCompartidaV::crear(int tam) {
	if (_creado == true || tam <= 0) {
		return -1;
	}

	_tamMemoria = tam;

	_clave = ftok(_rutaArch.c_str(), _idArch);

	if (_clave == -1) {
		std::string mensaje = std::string("Error en ftok() (MemCompV): ") + std::string(strerror(errno));
		throw mensaje;
		return -1;
	}

	// creacion de la memoria compartida

	this->_shmId = shmget(_clave, _tamMemoria, 0644|IPC_CREAT );

	if (_shmId == -1) {
		std::string mensaje = std::string("Error en shmget() (MemCompV): ") + std::string(strerror(errno));
		//throw mensaje;
		return -1;
	}

	// adosado de la memoria compartida
	_datos = shmat( _shmId, NULL, 0 );

	if (_datos == (void*)-1) {
		std::string mensaje = std::string("Error en shmat() (MemCompV): ") + std::string(strerror(errno));
		//throw mensaje;
		return -1;
	}

	_creado = true;
	return 0;
}

int MemCompartidaV::liberar() {

	if (_liberada == true)
		return 0;

	if (shmdt(_datos) != 0 ) {
		std::string mensaje = std::string("Error en shmdt() (MemCompV): ") + std::string(strerror(errno));
		throw mensaje;
	}


	if (this->procesosAdosados() == 0) {
		if (shmctl(_shmId, IPC_RMID, NULL) != 0) {
			std::string mensaje = std::string("Error en shmctl( , IPC_RMID , ) (MemCompV): ") + std::string(strerror(errno));
			throw mensaje;
		}
	}

	_liberada = true;
	return 0;
}

int MemCompartidaV::procesosAdosados() {
	shmid_ds estado;
	shmctl(_shmId,IPC_STAT,&estado);

	return estado.shm_nattch;
}

void* MemCompartidaV::datos() {
	return this->_datos;
}

int MemCompartidaV::tamanio() {
	return _tamMemoria;
}

MemCompartidaV::~MemCompartidaV() {
	this->liberar();
}

