/*
 * Recibidor.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "Recibidor.h"
#include "../common/Empaquetador.h"
#include "../common/GestorDeSeniales.h"
#include "../logger/Logger.h"

#include "AreaIntercambio.h"

#define TAG "RECIBIDOR_USUARIOS"

#include <string.h>

Recibidor* Recibidor::_instancia = NULL;


Recibidor::Recibidor() : _areaIntcmb() {
	_escuchando = true;
	_receptor.enlazar(PUERTO_SERVIDOR);

	_procesos = new Procesos();

	_semResolvedor = new SemaforoPSX(SEM_RESOLVEDOR, 1);

	_semIntercambio = new SemaforoPSX(SEM_INTERCAMBIO_RYR, 0);

	Logger::instance().debug(TAG, "Instanciando");
}

Recibidor::~Recibidor() {
	if (_semResolvedor != NULL)
		delete _semResolvedor;

	if (_semIntercambio != NULL)
		delete _semIntercambio;

	for (unsigned i = 0; i < _procesos->size() ; i++)
		delete (*_procesos)[i];

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

int Recibidor::comenzar(int pid) {

	Logger::instance().debug(TAG, "Iniciando.");

	_pidResolvedor = pid;

	Empaquetador emp;
	Paquete paq;
	DirSocket dirCliente;

	while(_escuchando) {

		if ( escuchar(paq,dirCliente) == 0 ) {
			emp.asociar(paq);

			Logger::instance().debug(TAG, "Nuevo Usuario escuchado");

			iniciarProcesoCliente(emp, dirCliente);

			transmitirAResolvedor();
		}

	}

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


void Recibidor::iniciarProcesoCliente(const Empaquetador& emp, const DirSocket& dirCliente) {

	Logger::instance().debug(TAG, "Lanzando proceos ReceptorMensajes");

	_ultimoProceso = new Process("./receptor");

	std::string nomUsr = emp.PAQ_nombreDeUsuario();


	std::string msj = std::string("Nuevo Usuario: ") + nomUsr;
	Logger::instance().debug(TAG, msj);


	NuevoUsuario info;
	info.pid_receptor = _ultimoProceso->getId();
	strncpy(info.nombre, nomUsr.c_str(), TAM_MAX_NOMBREUSR);
	info._dirSck = dirCliente;


	_areaIntcmb.escribir(info);
	Logger::instance().debug(TAG, "Escrita Info de Usuario en area de intercambio.");

	_procesos->push_back(_ultimoProceso);

}

void Recibidor::dejarDeEscuchar() {
	_escuchando = false;
}

void Recibidor::transmitirAResolvedor() {
	Logger::instance().debug(TAG, "Esperando que resolvedor se libere");
	_semResolvedor->wait();

	Logger::instance().debug(TAG, "Enviando señal a resolvedor por nuevo usuario.");
	GestorDeSeniales::instancia().enviarSenialAProceso(_pidResolvedor, SIGNUM_INTERCAMBIO_RESOLVEDOR);

	Logger::instance().debug(TAG, "Esperando que receptor lanzado confirme la sesion.");
	_semIntercambio->wait();

	Logger::instance().debug(TAG, "Confimacion Recibida y liberando al resolvedor para que continue.");
	_semResolvedor->signal();
}
