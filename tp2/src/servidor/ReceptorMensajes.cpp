/*
 * ReceptorMensajes.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "ReceptorMensajes.h"
#include "../common/Definiciones.h"
#include "../common/Empaquetador.h"
#include "../common/GestorDeSeniales.h"
#include "../logger/Logger.h"


#define TAG "RECEPTOR_MENSAJES"

ReceptorMensajes* ReceptorMensajes::_instancia = NULL;

ReceptorMensajes::ReceptorMensajes() :
		_receptor() {
	_receptor.enlazar(0);

	_seguirRecibiendo = true;

	GestorDeSeniales::instancia().agregarSenial(_senial);

	_semReceptor = new SemaforoPSX(SEM_INTERCAMBIO_RYR, 0);

	Logger::instance().debug(TAG, "Receptor instanaciado");
}

ReceptorMensajes::~ReceptorMensajes() {

}

ReceptorMensajes& ReceptorMensajes::instancia() {
	if (_instancia == NULL)
		_instancia = new ReceptorMensajes();
	return *_instancia;
}

bool ReceptorMensajes::instanaciado() {
	return (_instancia != NULL);
}

void ReceptorMensajes::liberar() {
	if (_instancia != NULL) {
		delete _instancia;
		_instancia = NULL;
	}
}

int ReceptorMensajes::comenzar() {

	Logger::instance().debug(TAG, "Iniciando receptor y esperando señal de continuacion.");

	Logger::instance().debug(TAG, "Por leer desde area de Intercambio.");
	NuevoUsuario info = areaIntcmb.leer();

	Logger::instance().debug(TAG, "Por enviar un signal() al recibidor para confirmacion inicio.");
	_semReceptor->signal();


	Logger::instance().debug(TAG, "Por esperar señal de confirmacion.");
	// ver si poner semaforo para sincronizar con resolvedor...
	GestorDeSeniales::instancia().enviarmeSenial(SIGNUM_ESPERA_CONFIRMACION);

	Logger::instance().debug(TAG, "Se recibio señal de confimacion");

	{
		Empaquetador emp;

		emp.limpiar();

		if (_seguirRecibiendo) {
			emp.confirmarRespuesta("Sesion Iniciada correctamente.");
			Logger::instance().debug(TAG, "Confirmacion de Inicio de Sesion.");
		}
		else {
			emp.agregarMensajeError("Error: Usuario ya existe");
			Logger::instance().debug(TAG, "Usuario ya existe, finalizara proceso");
		}

		_receptor.enviar(emp.paquete(), info._dirSck);
	}

	Paquete paqRecibido;

	while (_seguirRecibiendo) {
		_receptor.recibir(paqRecibido, _dirCliente);
		cola.insertar(paqRecibido);
	}

	Logger::instance().debug(TAG, "Finaliza recepcion de mensajes");

	return 0;
}


void ReceptorMensajes::dejarDeRecibir() {
	Logger::instance().debug(TAG, "Senial de finalizacion recibida");
	_seguirRecibiendo = false;
}
