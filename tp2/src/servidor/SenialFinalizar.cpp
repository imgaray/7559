/*
 * SenialFinalizar.cpp
 *
 *  Created on: 25/11/2013
 *      Author: migue
 */

#include "SenialFinalizar.h"
#include "../common/Definiciones.h"
#include "Resolvedor.h"
#include "Recibidor.h"

SenialFinalizar::SenialFinalizar() {
	this->agregarSenialABloquear(SIGNUM_FINALIZACION);
}

SenialFinalizar::~SenialFinalizar() {
}


int SenialFinalizar::numeroSenial() {
	return SIGNUM_FINALIZACION;
}

void SenialFinalizar::operacion() {
	if (Resolvedor::instanciado())
		Resolvedor::instanacia().dejarDeResponder();

	if (Recibidor::instanciado())
		Recibidor::instancia().dejarDeEscuchar();
}
