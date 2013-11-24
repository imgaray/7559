/*
 * Resolvedor.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "Resolvedor.h"
#include "../common/Empaquetador.h"


Resolvedor Resolvedor::_instancia;

Resolvedor::Resolvedor() :_emisor() {

	_emisor.enlazar(0);
	_ultimoIDLibre = 1;

}

Resolvedor& Resolvedor::instanacia() {
	return _instancia;
}

Resolvedor::~Resolvedor() {


}

const Paquete Resolvedor::resolver(const Paquete& origen, Destinatarios& destinos) {
	const Empaquetador emp(origen);
	Empaquetador respuesta;
	destinos.clear();

	if (emp.tipoActual() == Empaquetador::MENSAJE) {

	}
	else if (emp.tipoActual() == Empaquetador::INICIO_SESION) {
		respuesta.asociar(this->agregarUsuario(origen));
	}
	else if (emp.tipoActual() == Empaquetador::FIN_SESION) {

	}
	else if (emp.tipoActual() == Empaquetador::OK) {
		respuesta.limpiar();
	}
	else if (emp.tipoActual() == Empaquetador::CREAR_CONVERSACION) {
		respuesta.asociar(this->crearConversacion(emp, destinos));
	}
	else if (emp.tipoActual() == Empaquetador::UNIRSE_CONVERSACION) {

	}
	else if (emp.tipoActual() == Empaquetador::ERROR || emp.tipoActual() == Empaquetador::DESCONOCIDO) {

	}

	return respuesta.paquete();
}


const Paquete Resolvedor::agregarUsuario(const Paquete& paquete) {
	Empaquetador emp(paquete);

	std::string nomUsr = emp.nombreDeUsuario();

	itUsuarios it = _usuarios.find(nomUsr);
	if (it == _usuarios.end()) {
		emp.confirmarRespuesta();
		itUsuarios nUsr;
	}
	else {

	}

	return emp.paquete();
}

const Paquete Resolvedor::crearConversacion(const Empaquetador& empaquetador, Destinatarios& destinos){
	Empaquetador res;

	std::string nombreConversacion(empaquetador.nombreConversacion());

	if (nombreConversacion.size() == 0) {
		res.agregarMensajeError(std::string("No hay nombre para crear la nueva conversacion"));
		return res.paquete();
	}

	itConversaciones it = _conversaciones.find(nombreConversacion);

	if (it == _conversaciones.end()) {
		(*it).first = nombreConversacion;
		(*it).second = _ultimoIDLibre;
		_ultimoIDLibre++;
		res.confirmarRespuesta();
	}
	else {
		res.agregarMensajeError(std::string("Conversacion ya existe"));
	}


	return res.paquete();
}
