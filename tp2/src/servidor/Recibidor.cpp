/*
 * Recibidor.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "Recibidor.h"
#include "../common/Empaquetador.h"
#include "../common/GestorDeSeniales.h"

#include <string.h>

Recibidor* Recibidor::_instancia = NULL;


Recibidor::Recibidor() : _escuchando(true), _procesos() {
	_receptor.enlazar(PUERTO_SERVIDOR);

	_semResolvedor = new SemaforoPSX(SEM_RESOLVEDOR,1);

	_semIntercambio = new SemaforoPSX(SEM_INTERCAMBIO_RYR, 0);


	// TODO definir las señales para manejar
}

Recibidor::~Recibidor() {
	if (_semResolvedor != NULL)
		delete _semResolvedor;

	if (_semIntercambio != NULL)
		delete _semIntercambio;

	for (int i = 0; i < _procesos.size() ; i++)
		delete _procesos[i];
}

bool Recibidor::instanciado() {
	return (_instancia != NULL);
}

void Recibidor::liberar() {
	if (_instancia != NULL) {
		delete _instancia;
		_instancia = NULL;
	}
}

int Recibidor::comenzar(int pid) {

	_pidResolvedor = pid;

	Empaquetador emp;
	Paquete paq;
	DirSocket dirCliente;
	Process *proceso;

	while(_escuchando) {

		if ( escuchar(paq,dirCliente) == 0 ) {
			emp.asociar(paq);

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

	_ultimoProceso = new Process("./receptor");

	std::string nomUsr = emp.PAQ_nombreDeUsuario();

	NuevoUsuario info;
	info.pid_receptor = _ultimoProceso->getId();
	strncpy(info.nombre, nomUsr.c_str(), TAM_MAX_NOMBREUSR);
	info._dirSck = dirCliente;

	_areaIntcmb.escribir(info);
	_procesos.push_back(_ultimoProceso);

}

void Recibidor::dejarDeEscuchar() {
	_escuchando = false;
}

void Recibidor::transmitirAResolvedor() {
	_semResolvedor->wait();
	GestorDeSeniales::instancia().enviarSenialAProceso(_pidResolvedor, SIGNUM_INTERCAMBIO_RESOLVEDOR);

	_semIntercambio->wait();
	_semResolvedor->signal();
}
