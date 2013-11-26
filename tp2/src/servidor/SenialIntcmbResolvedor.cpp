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

#include "AreaIntercambio.h"
#include "Resolvedor.h"

SenialIntcmbResolvedor::SenialIntcmbResolvedor() {
	this->agregarSenialABloquear(SIGINT);
}

SenialIntcmbResolvedor::~SenialIntcmbResolvedor() {
}

int SenialIntcmbResolvedor::numeroSenial() {
	return SIGNUM_INTERCAMBIO_RESOLVEDOR;
}

void SenialIntcmbResolvedor::operacion() {
	AreaIntercambio intercambio;

	Resolvedor& resolvedor = Resolvedor::instanacia();
	GestorDeSeniales& gestorSen = GestorDeSeniales::instancia();

	NuevoUsuario nuevoUsr;
	nuevoUsr = intercambio.leer();

	Empaquetador emp;

	std::string nombreUsuario = nuevoUsr.nombre;

	emp.iniciarSesion(nombreUsuario);

	Destinatarios dest;

	resolvedor.usarSemaforos(false);

	// se envia el paquete de inicio al resolvedor
	Paquete res = resolvedor.resolver(emp.paquete(),dest);

	emp.asociar(res);

	InfoUsuario info;
	info._dirSock = nuevoUsr._dirSck;
	info.pid = nuevoUsr.pid_receptor;
	info.id_conv = 0;


	if (emp.PAQ_confirmacionRecibida()) {
		// se confirma al proceso que continue que se confirmo el inicio sesion
		gestorSen.enviarSenialAProceso(info.pid, SIGNUM_CONFIRMACION);
	}
	else {
		// No se pudo crear sesion, lo mas comun es porque se encontro usuario con mismo nombre
		// envia señal para que finaliza el proceso
		gestorSen.enviarSenialAProceso(info.pid, SIGNUM_CONFIRMACION_NEGATIVA);
	}

	resolvedor.usarSemaforos(true);
}

