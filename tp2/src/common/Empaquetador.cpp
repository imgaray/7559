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

void Empaquetador::agregarMensaje(const std::string& mensaje) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::MENSAJE);

	_paquete.agregarDatos((void*) mensaje.c_str(), mensaje.size());
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

void Empaquetador::agregarConversaciones(std::vector<std::string> conversaciones) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::CONVERSACIONES);

	std::vector<std::string>::iterator it = conversaciones.begin();

	while (it != conversaciones.end()) {
		_paquete.agregarAtributo((void*) (*it).c_str(), (*it).size());
		it++;
	}
}

const std::string Empaquetador::nombreUsuario() const {
	std::string nombre;
	nombre.clear();

	if (iniciandoSesion()) {
		nombre = _paquete.mensaje();
	}

	return nombre;
}

const std::vector<std::string> Empaquetador::conversaciones() const {
	std::vector<std::string> conj;

	int ind = 0;

	char* conv = _paquete.atributo(0);

	while (conv != NULL) {
		ind++;
		conj[ind]=std::string(conv);
		delete conv;

		conv = _paquete.atributo(ind);
	}


	return conj;
}

const std::string Empaquetador::mesaje() const {
	return _paquete.mensaje();
}

bool Empaquetador::iniciandoSesion() const {
	return (_paquete.tipo() == Empaquetador::INICIO_SESION);
}
bool Empaquetador::finalizandoSesion() const {
	return (_paquete.tipo() == Empaquetador::FIN_SESION);
}

bool Empaquetador::confirmacionRecibida() const {
	return (_paquete.tipo() == Empaquetador::OK);
}

bool Empaquetador::errorRecibido() const {
	return (_paquete.tipo() == Empaquetador::ERROR);
}

Empaquetador::TipoPaquete Empaquetador::tipoActual() const {
	return (Empaquetador::TipoPaquete) _paquete.tipo();
}

const Paquete& Empaquetador::paquete() const {
	return _paquete;
}
