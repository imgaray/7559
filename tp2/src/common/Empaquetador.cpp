/*
 * Empaquetador.cpp
 *
 *  Created on: 16/11/2013
 *      Author: migue
 */

#include "Empaquetador.h"

Empaquetador::Empaquetador() : _paquete() {

}

Empaquetador::Empaquetador(const Paquete& paquete) : _paquete() {
	_paquete = paquete;
}

Empaquetador::~Empaquetador() {

}

void Empaquetador::agregarMensajeError(const std::string& mensaje) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::ERROR);
	_paquete.agregarDatos((void*)mensaje.c_str(), mensaje.size());
}

void Empaquetador::iniciarSesion(const std::string& nombreUsuario) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::INICIO_SESION);
	_paquete.agregarDatos((void*) nombreUsuario.c_str(), nombreUsuario.size());

}

void Empaquetador::crearConversacion(std::string& nombreNuevaConversacion) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::CREAR_CONVERSACION);
	_paquete.agregarDatos((void*) nombreNuevaConversacion.c_str(), nombreNuevaConversacion.size());
}

void Empaquetador::finalizarSesion() {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::FIN_SESION);
}

void Empaquetador::confirmarRespuesta() {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::OK);
}

