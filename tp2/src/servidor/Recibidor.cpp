/*
 * Recibidor.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "Recibidor.h"

Recibidor Recibidor::_instancia;


Recibidor::Recibidor() : _escuchando(false) {
	_receptor.enlazar(PUERTO_SERVIDOR);

	// TODO definir las señales para manejar

}

Recibidor::~Recibidor() {

}

int Recibidor::comenzar() {
	Empaquetador emp;
	Paquete paq;
	DirSocket dirCliente;

	while(_escuchando) {

		if ( escuchar(paq,dirCliente) == 0 ) {
			transmitir(paq, dirCliente);
		}

	}

	return 0;
}

Recibidor& Recibidor::instancia() {
	return _instancia;
}
