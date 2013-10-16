#include "Avion.h"
#include <string.h>
#include <iostream>

#define SEP ';'

void Avion::accionar() {
	this->estrategia.operar();
}

Avion::Avion(const Avion& avion): estrategia(avion.estrategia) {
}

Avion::Avion(const EstrategiaAvion& estrategia): estrategia(estrategia) {
}

Avion::Avion(const std::string& s){
	deserializar(s);
}

Avion::~Avion() {
}

bool Avion::operator<(const Avion& avion) const {
	return this->estrategia < avion.estrategia;
}

const char* Avion::serializar(){
	
	static char serial[32];
	std::stringstream ss;
	
	ss << "AVION" << SEP << determinarPrioridad();
	ss >> serial ;
	
	return serial;
}

void Avion::deserializar (const std::string& s){
	Utilitario utilitario;
	int codEstrategia = utilitario.convertirAEntero( utilitario.separar(s, SEP, 1) );
	if (codEstrategia == 0)
		this->estrategia = EstrategiaAvion (TIERRA);
	else if (codEstrategia == 1)
		this->estrategia = EstrategiaAvion (AIRE);

}

int Avion::determinarPrioridad(){
	return this->estrategia.determinarPrioridad();
}
