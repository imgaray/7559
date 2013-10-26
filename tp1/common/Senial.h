/*
 * Senial.h
 *
 *  Created on: 25/10/2013
 *      Author: migue
 */

#ifndef SENIAL_H_
#define SENIAL_H_

#include <signal.h>
#include <set>

/**
 * Clase abstracta que respresnta el manejo de una señal.
 */

class Senial {
public:
	Senial();

	/**
	 * Devuelve el numeor que señal que se representa, definidos como int en
	 * signum.h (que esta incluido en la cabecera signal.h) ,
	 * Ej: SINGINT, SIGINT, SIGKILL, SIGSTOP, etc.
	 *
	 */
	virtual int numeroSenial() = 0;

	/**
	 * Metodo invocado cuando se recive la señal. Al finalizar continua con la
	 * ejecucion del proceso desde el mismo lugar donde se encontraba.
	 */
	virtual void operacion() = 0;

	/**
	 * Conjunto de señales que se debe bloquear l ejecutar el
	 * metodo operacion
	 */
	const std::set<int>& senialesBloqueadas();

	/**
	 * Agrega la señal que se quiere bloquear durante la ejecucion de esta señal.
	 */
	void agregarSenialABloquear(int sigNum);

	virtual ~Senial();

private:
	std::set<int> _sBloqueadas;
};

#endif /* SENIAL_H_ */
