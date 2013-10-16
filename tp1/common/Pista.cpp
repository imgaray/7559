#include "Pista.h"
#include <string.h>

#define SEP ';'

void Pista::tomar() {
}

void Pista::liberar() {
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
