/*
 * Senial.cpp
 *
 *  Created on: 25/10/2013
 *      Author: migue
 */

#include "Senial.h"


Senial::Senial() {

}


Senial::~Senial() {

}

void Senial::agregarSenialABloquear(int sigNum) {
	_sBloqueadas.insert(sigNum);
}

const std::set<int>& Senial::senialesBloqueadas() {
	return _sBloqueadas;
}
