/*
 * SenialIntcmbResolvedor.cpp
 *
 *  Created on: 25/11/2013
 *      Author: migue
 */

#include "SenialIntcmbResolvedor.h"

#include "../common/Definiciones.h"
#include "../common/Empaquetador.h"
#include "../common/GestorDeSeniales.h"
#include "../common/SemaforoPSX.h"

#include "../logger/Logger.h"

#include "AreaIntercambio.h"
#include "Resolvedor.h"

#define TAG "RESOLVEDOR_SENIAL_INTCMB"

SenialIntcmbResolvedor::SenialIntcmbResolvedor() {
	this->agregarSenialABloquear(SIGNUM_FINALIZACION);
	this->agregarSenialABloquear(SIGNUM_INTERCAMBIO_RESOLVEDOR);
}

SenialIntcmbResolvedor::~SenialIntcmbResolvedor() {
}

int SenialIntcmbResolvedor::numeroSenial() {
	return SIGNUM_INTERCAMBIO_RESOLVEDOR;
}

void SenialIntcmbResolvedor::operacion() {

	/*
	SemaforoPSX semConfirmacion(SEM_CONFIRMACION_RECEPTOR, 0);
	semConfirmacion.inicializar();

	Logger::instance().debug(TAG, "Iniciando tratamiento de intercambio.");

	AreaIntercambio intercambio;

	Resolvedor& resolvedor = Resolvedor::instancia();
	GestorDeSeniales& gestorSen = GestorDeSeniales::instancia();

	NuevoUsuario nuevoUsr;

	Logger::instance().debug(TAG, "Leyendo datos de nuevo usuario.");
	nuevoUsr = intercambio.leer();

	Empaquetador emp;

	std::string nombreUsuario = nuevoUsr.nombre;
	Logger::instance().debug(TAG, nuevoUsr.nombre);

	Logger::instance().debug(TAG, "Creando paquete de inicio de sesion..");
	emp.iniciarSesion(nombreUsuario);

	Destinatarios dest;

	Logger::instance().debug(TAG, "Deshabilitando semaforos del resolvedor.");
	resolvedor.usarSemaforos(false);


	Logger::instance().debug(TAG, "Por resolver paquete leido .");
	// se envia el paquete de inicio al resolvedor

	Paquete res =resolvedor.agregarNuevoUsuario(nuevoUsr);

	emp.asociar(res);

	InfoUsuario info;
	info._dirSock = nuevoUsr._dirSck;
	info.pid = nuevoUsr.pid_receptor;
	info.id_conv = 0;

	Logger::instance().debug(TAG, "Esperando que inicie Receptor y se detenga para esperar confirmacion.");
	semConfirmacion.wait();

	if (emp.PAQ_confirmacionRecibida()) {
		Logger::instance().debug(TAG, "Enviando señal de confirmacion al receptor de Mensajes.");
		// se confirma al proceso que continue ya que se confirmo el inicio sesion
		gestorSen.enviarSenialAProceso(info.pid, SIGNUM_CONFIRMACION);
	}
	else {
		Logger::instance().debug(TAG, "Enviando señal de finalizacion al receptor de Mensajes.");
		// No se pudo crear sesion, lo mas comun es porque se encontro usuario con mismo nombre
		// envia señal que finaliza el proceso
		gestorSen.enviarSenialAProceso(info.pid, SIGNUM_CONFIRMACION_NEGATIVA);
		gestorSen.enviarSenialAProceso(info.pid, SIGNUM_CONFIRMACION);
	}

	Logger::instance().debug(TAG, "Habilitando semaforos del resolvedor.");

	resolvedor.senialTratada();
	resolvedor.usarSemaforos(true);
	*/
}

