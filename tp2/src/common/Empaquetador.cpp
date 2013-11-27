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

void Empaquetador::asociar(const Paquete& paquete) {
	_paquete = paquete;
}

void Empaquetador::agregarMensaje(const std::string& nombreUsuario, const std::string& mensaje) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::MENSAJE);

	_paquete.agregarAtributo((void*) nombreUsuario.c_str(), nombreUsuario.size());
	_paquete.agregarAtributo((void*) mensaje.c_str(), mensaje.size());
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

void Empaquetador::crearConversacion(const std::string& nomUsuario,const std::string& nombreNuevaConversacion) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::CREAR_CONVERSACION);

	_paquete.agregarAtributo((void*) nomUsuario.c_str(), nomUsuario.size());
	//_paquete.agregarDatos((void*) nombreNuevaConversacion.c_str(), nombreNuevaConversacion.size());
	_paquete.agregarAtributo((void*) nombreNuevaConversacion.c_str(), nombreNuevaConversacion.size());

}

void Empaquetador::finalizarSesion(const std::string& nombreUsuario) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::FIN_SESION);

	_paquete.agregarAtributo((void*)nombreUsuario.c_str(), nombreUsuario.size());
}

void Empaquetador::confirmarRespuesta() {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::OK);
}

void Empaquetador::confirmarRespuesta(const std::string& mensaje) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::OK);
	_paquete.agregarAtributo((void*)mensaje.c_str(), mensaje.size());
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

const std::string Empaquetador::PAQ_nombreDeUsuario() const {
	std::string nombre;
	nombre.clear();

	if (PAQ_iniciandoSesion()) {
		nombre = _paquete.mensaje();
	}
	else if (_paquete.tipo() == Empaquetador::MENSAJE
			|| _paquete.tipo() == Empaquetador::CREAR_CONVERSACION
			|| _paquete.tipo() == Empaquetador::UNIRSE_CONVERSACION
			|| _paquete.tipo() == Empaquetador::CONVERSACIONES
			|| _paquete.tipo() == Empaquetador::FIN_SESION
			|| _paquete.tipo() == Empaquetador::INICIO_SESION){
		char* cres = _paquete.atributo(0);

		if (cres != NULL) {
			nombre = cres;
			delete cres;
		}
	}

	return nombre;
}


void Empaquetador::unirseConversacion(const std::string& nomUsuario, const std::string& nombreConversacion) {
	_paquete.limpiar();
	_paquete.definirTipo(Empaquetador::UNIRSE_CONVERSACION);

	_paquete.agregarAtributo((void*)nomUsuario.c_str(), nomUsuario.size());
	_paquete.agregarAtributo((void*)nombreConversacion.c_str(), nombreConversacion.size());

}


const std::vector<std::string> Empaquetador::PAQ_conversaciones() const {
	std::vector<std::string> conj;

	int ind = 0;


	if (_paquete.tipo() == Empaquetador::CONVERSACIONES) {

		char* conv = _paquete.atributo(0);

		while (conv != NULL) {
			ind++;
			//conj[ind]=std::string(conv);
			conj.push_back(std::string(conv));

			delete conv;

			conv = _paquete.atributo(ind);
		}
	}

	return conj;
}

void Empaquetador::verConversaciones(const std::string& nombreUsuario) {
	_paquete.limpiar();

	_paquete.definirTipo(Empaquetador::CONVERSACIONES);
	_paquete.agregarAtributo((void*) nombreUsuario.c_str(), nombreUsuario.size());

}

const std::string Empaquetador::PAQ_nombreConversacion() const {
	std::string res;

	if (_paquete.tipo() == Empaquetador::CREAR_CONVERSACION || _paquete.tipo() == Empaquetador::UNIRSE_CONVERSACION) {
		char* cres = _paquete.atributo(1);

		if (cres != NULL) {
			res = cres;
			delete cres;
		}
	}

	return res;
}

const std::string Empaquetador::PAQ_mensajeDeUsuario() const {
	std::string res;

	if (_paquete.tipo() == Empaquetador::MENSAJE ||
			_paquete.tipo() == Empaquetador::OK ) {
		char* cres = _paquete.atributo(1);

		if ( cres != NULL ) {
			res = cres;
			delete cres;
		}
	}

	return res;
}


const std::string Empaquetador::PAQ_mensajeDeError() const {
	std::string res;

	if (_paquete.tipo() == Empaquetador::ERROR) {
		res = _paquete.mensaje();
	}

	return res;
}

bool Empaquetador::PAQ_iniciandoSesion() const {
	return (_paquete.tipo() == Empaquetador::INICIO_SESION);
}
bool Empaquetador::PAQ_finalizandoSesion() const {
	return (_paquete.tipo() == Empaquetador::FIN_SESION);
}

bool Empaquetador::PAQ_confirmacionRecibida() const {
	return (_paquete.tipo() == Empaquetador::OK);
}

bool Empaquetador::PAQ_errorRecibido() const {
	return (_paquete.tipo() == Empaquetador::ERROR);
}

Empaquetador::TipoPaquete Empaquetador::tipoActual() const {
	return (Empaquetador::TipoPaquete) _paquete.tipo();
}

const Paquete& Empaquetador::paquete() const {
	return _paquete;
}

void Empaquetador::limpiar() {
	_paquete.limpiar();
}
