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
	
	char* serial = new char[32];
	std::stringstream ss;
	std::string output;
	
	ss << "AVION" << SEP << determinarPrioridad();
	ss >> output;
	int i = 0;
	for (; i < output.size(); i++) {
		serial[i] = output[i];
	}
	for (; i < 30; i++) {
		*(serial + i) = 'X';
	}
	serial[31] = '\0';
	return serial;
}

void Avion::deserializar (const std::string& s){
	Utilitario utilitario;
	int codEstrategia = utilitario.convertirAEntero( utilitario.separar(s, SEP, 0) );
	if (codEstrategia == 0)
		this->estrategia = EstrategiaAvion (TIERRA);
	else if (codEstrategia == 1)
		this->estrategia = EstrategiaAvion (AIRE);

}

int Avion::determinarPrioridad(){
	return this->estrategia.determinarPrioridad();
}
