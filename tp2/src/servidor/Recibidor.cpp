/*
 * Recibidor.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "Recibidor.h"

#include <iostream>

#include "../common/Empaquetador.h"
#include "../common/GestorDeSeniales.h"
#include "../common/Utilitario.h"
#include "../logger/Logger.h"

#include "AreaIntercambio.h"

#define TAG "RECIBIDOR_USUARIOS"

#include <string.h>

Recibidor* Recibidor::_instancia = NULL;


Recibidor::Recibidor() : _areaIntcmb() {
	_escuchando = true;
	_receptor.enlazar(PUERTO_SERVIDOR);

	_procesos = new Procesos();

	_semIntercambio = new SemaforoPSX(SEM_INTERCAMBIO_RYR, 0);
	_semRecibidor = new SemaforoPSX(SEM_RECIBIDOR, 1);

	Logger::instance().debug(TAG, "Instanciando");

	GestorDeSeniales::instancia().agregarSenial(_senialFin);
}

Recibidor::~Recibidor() {
	if (_semIntercambio != NULL)
		delete _semIntercambio;

	if (_semRecibidor != NULL)
		delete _semRecibidor;

	Utilitario u;
	std::string msj;
	for (unsigned i = 0; i < _procesos->size() ; i++) {
		msj = std::string("Finalizando receptor pid: ") + u.convertirAString((*_procesos)[i]->getId());
		Logger::instance().debug(TAG, msj);
		GestorDeSeniales::instancia().enviarSenialAProceso((*_procesos)[i]->getId(), SIGNUM_FINALIZACION);
	}

	for (unsigned i = 0; i < _procesos->size() ; i++) {
		delete (*_procesos)[i];
	}

	delete _procesos;
}

bool Recibidor::instanciado() {
	return (_instancia != NULL);
}

void Recibidor::liberar() {
	Logger::instance().debug(TAG, "Liberando.");
	if (_instancia != NULL) {
		delete _instancia;
		_instancia = NULL;
	}
}

int Recibidor::comenzar() {

	Logger::instance().debug(TAG, "Iniciando.");

	Empaquetador emp;
	Paquete paq;
	DirSocket dirCliente;

	while(_escuchando) {

		if ( escuchar(paq,dirCliente) == 0 ) {
			emp.asociar(paq);

			Logger::instance().debug(TAG, "Nuevo Usuario escuchado");

			procesarSolicitud(emp, dirCliente);

		}

	}

	Logger::instance().debug(TAG, "Finalizando la \"escucha\" de nuevos usuarios.");

	return 0;
}

Recibidor& Recibidor::instancia() {
	if (_instancia == NULL)
		_instancia = new Recibidor();
	return *_instancia;
}

int Recibidor::escuchar(Paquete& paq, DirSocket& dir) {
	if (_receptor.recibir(paq, dir) == true)
		return 0;
	else
		return -1;
}


void Recibidor::procesarSolicitud(const Empaquetador& emp, const DirSocket& dirCliente) {
	_semRecibidor->wait();

	Logger::instance().debug(TAG, "Lanzando proceso ReceptorMensajes");


	_semIntercambio->inicializar();

	std::string rutaProceso = "./appReceptor";
	_ultimoProceso = new Process(rutaProceso);

	// esperar hasta que inicie el proceso Receptor

	std::string nomUsr = emp.PAQ_nombreDeUsuario();

	std::string msj = std::string("Nuevo Usuario: ") + nomUsr;
	Logger::instance().debug(TAG, msj);

	NuevoUsuario info;
	info.pid_receptor = _ultimoProceso->getId();
	strncpy(info.nombre, nomUsr.c_str(), TAM_MAX_NOMBREUSR);
	info._dirSck = dirCliente;


	Logger::instance().debug(TAG, "Escrita Info de Usuario en area de intercambio.");
	_areaIntcmb.escribir(info);

	_semIntercambio->wait();

	Empaquetador emp2;
	emp2.protoInicio(info);
	Logger::instance().debug(TAG, "Se esta por colocar paquete de inicio de sesion en la cola.");
	_cola.insertar(emp2.paquete());
	Logger::instance().debug(TAG, "Se coloco paquete de inicio de sesion en al cola.");

	_procesos->push_back(_ultimoProceso);

	_semRecibidor->signal();
}

void Recibidor::dejarDeEscuchar() {
	Logger::instance().debug(TAG, "Senial de finalizacion recibida");
	_escuchando = false;
}
