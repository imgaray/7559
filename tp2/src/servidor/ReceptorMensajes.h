/*
 * ReceptorMensajes.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef RECEPTORMENSAJES_H_
#define RECEPTORMENSAJES_H_

/**
 * Clase encargada de resivir todos los mensajes de un cliente que ya inicio sesion.
 */

class ReceptorMensajes {
public:
	ReceptorMensajes();
	virtual ~ReceptorMensajes();

	int comenzar();

private:

	// poner la cola de PaqueteEntrantes

	// leer area de Intercambio que dejo el Receptor
	// Semaforo de Area de intercambio, solo para avisa al proceso padre que ya lo leyo los datos
};

#endif /* RECEPTORMENSAJES_H_ */
