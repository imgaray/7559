/*
 * GestorDeSeniales.cpp
 *
 *  Created on: 25/10/2013
 *      Author: migue
 */

#include "GestorDeSeniales.h"
#include <signal.h>
#include <sys/types.h>

GestorDeSeniales GestorDeSeniales::_instancia;

GestorDeSeniales::GestorDeSeniales() {
	_seniales = new std::map<int, Senial*>();
}

GestorDeSeniales::~GestorDeSeniales() {
	delete _seniales;
}

void GestorDeSeniales::agregarSenial(Senial& senial) {
	struct sigaction _sa;

	sigemptyset(&_sa.sa_mask);
	_sa.sa_handler = GestorDeSeniales::lanzarSenial;
	_sa.sa_flags = 0;

	std::set<int> senialesBloqueadas = senial.senialesBloqueadas();
	std::set<int>::iterator it = senialesBloqueadas.begin();

	while (it != senialesBloqueadas.end()) {
		sigaddset(&_sa.sa_mask, *it);
		it++;
	}

	sigaction(senial.numeroSenial(), &_sa, 0);

	(*_seniales)[senial.numeroSenial()] = &senial;

}

GestorDeSeniales& GestorDeSeniales::instancia() {
	return _instancia;
}

void GestorDeSeniales::lanzarSenial(int parametro) {
	std::map<int, Senial*>::iterator it;
	it = _instancia._seniales->find(parametro);


	if (it != _instancia._seniales->end()) {
		it->second->operacion();
	}

}

void GestorDeSeniales::enviarSenialAProceso(int pid, int SIGNUM) {
	kill(pid, SIGNUM);
}


void GestorDeSeniales::enviarmeSenial(int SIGNUM) {
	raise(SIGNUM);
}
