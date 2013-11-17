/*
 * Empaquetador.h
 *
 *  Created on: 16/11/2013
 *      Author: migue
 */


/**
 * Tipos de Paquetes (formatos y sus datos)
 *
 *
 * TAM || MENSAJE || tamString | NombreConversacion || "mesaje"
 *
 * TAM || FIN_SESION
 *
 * TAM || INICIO_SESION || Nombre
 *
 * TAM || CONVERSACIONES || #Listado de Conversaciones (tamString || nombre)
 *
 * TAM || CREAR_CONVERSACION || NombreNuevaConversacion
 *
 * TAM || UNIRSE_CONVERSACION || NombreConversacion
 *
 * TAM || ERROR || "Mensaje de Error"
 *
 */


#ifndef EMPAQUETADOR_H_
#define EMPAQUETADOR_H_


#include "Paquete.h"
#include <set>

class Empaquetador {
public:
	Empaquetador();
	Empaquetador(const Paquete& paquete);
	virtual ~Empaquetador();

	enum TipoPaquete {
			DESCONOCIDO = 0,

			INICIO_SESION,
			FIN_SESION,

			MENSAJE,

			CREAR_CONVERSACION,
			UNIRSE_CONVERSACION,

			CONVERSACIONES,

			OK,
			ERROR
		};


	/**
	 * Metodos que utilizara el emisor
	 */
	void agregarNombreUsuario(std::string& nombreUsuario);

	void agregarConversaciones(std::set<std::string> conversaciones);
	void agregarMensaje(const std::string& mensaje);
	void agregarMensajeError(const std::string& mensaje);
	void crearConversacion(std::string& nombreNuevaConversacion);

	void iniciarSesion(const std::string& nombreUsuario);
	void finalizarSesion();

	void confirmarRespuesta();

	/**
	 * Metodos que usar el receptor
	 */
	const std::string nombreUsuario() const;

	const std::string mesaje() const;
	const std::set<std::string> conversaciones() const;
	bool iniciandoSesion() const;
	bool finalizandoSesion() const;

	bool confirmacionRecibida() const;
	bool errorRecibido() const;

	TipoPaquete tipoActual() const;

	const Paquete& paquete() const;

private:
	Paquete _paquete;
};

#endif /* EMPAQUETADOR_H_ */
