#include "Pista.h"
#include <string.h>
#include <iostream>

#define SEP ';'

void Pista::tomar() {
	std::cout << "PISTA " << numero << " TOMADA" << std::endl;
}

void Pista::liberar() {
	std::cout << "PISTA " << numero << " LIBERADA" << std::endl;
}

Pista::Pista(unsigned numero): numero(numero) {
}

Pista::Pista(const std::string& s) {
	deserializar(s);
}

Pista::~Pista() {
}

const char* Pista::serializar(){
	Utilitario utilitario;
	
	static char serial[32];
	std::stringstream ss;
	
	ss << "PISTA" << SEP << utilitario.convertirAString(numero) << SEP << this->lock->getNombre();
	ss >> serial ;

	return serial;
}

void Pista::deserializar (const std::string& s){
	Utilitario utilitario;
	this->numero = utilitario.convertirAEntero( utilitario.separar(s, SEP, 1) );
}
