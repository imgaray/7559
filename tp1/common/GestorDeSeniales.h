/*
 * GestorDeSeniales.h
 *
 *  Created on: 25/10/2013
 *      Author: migue
 */

#ifndef GESTORDESENIALES_H_
#define GESTORDESENIALES_H_

#include <map>
#include "Senial.h"

/**
 * Clase Singleton que administra el manejo
 */

class GestorDeSeniales {
public:

	/**
	 * Retorna la unica instancia del Gestor
	 */
	static GestorDeSeniales& instancia();

	/**
	 * Agrega un referencia de una señal,
	 */
	void agregarSenial(Senial& senial);

	/**
	 * Envia una señal al proceso con identificador pid
	 *  pid: process id del proceso que recibira la señal
	 *  SIGNUM: int que representa a la señal
	 */
	void enviarSenialAProceso(int pid, int SIGNUM);

	virtual ~GestorDeSeniales();

private:

	std::map<int, Senial*>* _seniales;

	GestorDeSeniales();
	static GestorDeSeniales _instancia;
	static void lanzarSenial(int parametro);
};

#endif /* GESTORDESENIALES_H_ */
