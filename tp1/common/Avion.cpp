#include "Avion.h"
#include <string.h>

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
	
}

int Avion::determinarPrioridad(){
	return this->estrategia.determinarPrioridad();
}
