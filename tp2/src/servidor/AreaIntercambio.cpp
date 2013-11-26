/*
 * AreaIntercambio.cpp
 *
 *  Created on: 25/11/2013
 *      Author: migue
 */

#include "AreaIntercambio.h"

AreaIntercambio::AreaIntercambio() : _memComp(NULL) {
	_memComp = new MemoriaCompartida<NuevoUsuario>(MC_INTCMB_RECIBIDOR, PROJ_ID_RECIBIDOR);
}

AreaIntercambio::~AreaIntercambio() {
	delete _memComp;
}

void AreaIntercambio::destruir() {
	if (_memComp != NULL)
		_memComp->liberar();
}

const NuevoUsuario AreaIntercambio::leer() {
	return _memComp->leer();
}

void AreaIntercambio::escribir(const NuevoUsuario& info) {
	_memComp->escribir(info);
}


