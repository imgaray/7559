/*
 * SenialFinalizar.cpp
 *
 *  Created on: 25/11/2013
 *      Author: migue
 */

#include "SenialFinalizar.h"
#include "../common/Definiciones.h"
#include "../logger/Logger.h"

#include "Resolvedor.h"
#include "Recibidor.h"
#include "ReceptorMensajes.h"

#define TAG "SENIAL FINALIZACION"

SenialFinalizar::SenialFinalizar() {
	//this->agregarSenialABloquear(SIGNUM_FINALIZACION);
}

SenialFinalizar::~SenialFinalizar() {
}


int SenialFinalizar::numeroSenial() {
	return SIGNUM_FINALIZACION;
}

void SenialFinalizar::operacion() {

	Logger::instance().debug(TAG, "Llamado a tratamiento de senial");

	if (Resolvedor::instanciado())
		Resolvedor::instancia().dejarDeResponder();

	if (Recibidor::instanciado())
		Recibidor::instancia().dejarDeEscuchar();

	if (ReceptorMensajes::instanaciado())
		ReceptorMensajes::instancia().dejarDeRecibir();
}
