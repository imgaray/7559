#include "Avion.h"

#define SEP ';'

void Avion::accionar() {
	this->estrategia.operar();
}

Avion::Avion(const Avion& avion): estrategia(avion.estrategia) {
}

Avion::Avion(const EstrategiaAvion& estrategia): estrategia(estrategia) {
}

Avion::Avion(const std::string& s, const EstrategiaAvion& estrategia): estrategia(estrategia) {
	deserializar(s);
}

Avion::~Avion() {
}

bool Avion::operator<(const Avion& avion) const {
	return this->estrategia < avion.estrategia;
}

std::string Avion::serializar(){
	Utilitario utilitario;
	std::string serial = "AVION";
	serial += SEP;
	
	return serial;
}

void Avion::deserializar (const std::string& s){
	
}
