/*
 * SenialFinalizacion.cpp
 *
 *  Created on: 26/11/2013
 *      Author: migue
 */

#include "SenialFinalizacion.h"
#include "../common/Definiciones.h"

extern bool _seguirRecibiendo_;

SenialFinalizacion::SenialFinalizacion() {
	this->agregarSenialABloquear(SIGNUM_FINALIZACION);
}

SenialFinalizacion::~SenialFinalizacion() {
}


int SenialFinalizacion::numeroSenial() {
	return SIGNUM_FINALIZACION;
}

void SenialFinalizacion::operacion() {
	_seguirRecibiendo_ = false;
}
