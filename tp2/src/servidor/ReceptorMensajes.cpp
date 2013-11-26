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

ReceptorMensajes* ReceptorMensajes::_instancia = NULL;

ReceptorMensajes::ReceptorMensajes() :
		_seguirRecibiendo(true),
		_semReceptor(SEM_INTERCAMBIO_RYR, 0),
		_receptor() {
	_receptor.enlazar(0);

	GestorDeSeniales::instancia().agregarSenial(_senial);
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
	// ver si poner semaforo para sincronizar con resolvedor...
	GestorDeSeniales::instancia().enviarmeSenial(SIGNUM_ESPERA_CONFIRMACION);
	_semReceptor.signal();

	NuevoUsuario info = areaIntcmb.leer();

	{
		Empaquetador emp;

		if (_seguirRecibiendo)
			emp.confirmarRespuesta("Sesion Iniciada");
		else
			emp.agregarMensajeError("Error: Usuario ya existe");


		_receptor.enviar(emp.paquete(), info._dirSck);
	}

	Paquete paqRecibido;

	while (_seguirRecibiendo) {
		_receptor.recibir(paqRecibido, _dirCliente);
		cola.insertar(paqRecibido);
	}

	return 0;
}


void ReceptorMensajes::dejarDeRecibir() {
	_seguirRecibiendo = false;
}
