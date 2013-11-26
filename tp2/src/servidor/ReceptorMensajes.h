/*
 * ReceptorMensajes.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef RECEPTORMENSAJES_H_
#define RECEPTORMENSAJES_H_

#include <unistd.h>
#include "../common/Definiciones.h"
#include "../common/GestorDeSeniales.h"
#include "../common/SemaforoPSX.h"
#include "AreaIntercambio.h"


#include "ColaDePaquetes.h"


/**
 * Clase encargada de resivir todos los mensajes de un cliente que ya inicio sesion.
 */

class ReceptorMensajes {
public:

	virtual ~ReceptorMensajes();

	int comenzar();

	void dejarDeRecibir();

	static ReceptorMensajes& instancia();
	static void liberar();

private:
	ReceptorMensajes();
	ReceptorMensajes(const ReceptorMensajes& orig);


	ColaDePaquetes cola;
	AreaIntercambio areaIntcmb;
	SemaforoPSX _semReceptor;
	GestorDeSeniales& _gestor;

	DirSocket _dirCliente;

	bool _seguirRecibiendo;

	SocketUDP _receptor;

	static ReceptorMensajes* _instancia;

	// poner la cola de PaqueteEntrantes

	// leer area de Intercambio que dejo el Receptor
	// Semaforo de Area de intercambio, solo para avisa al proceso padre que ya lo leyo los datos
};

#endif /* RECEPTORMENSAJES_H_ */
