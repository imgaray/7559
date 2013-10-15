#include "Pista.h"

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

std::string Pista::serializar(){
	Utilitario utilitario;
	std::string serial = "PISTA";
	serial += SEP;
	serial += utilitario.convertirAString(numero);
	serial += SEP;
	serial += this->lock->getNombre();
	serial += SEP;
	
	return serial;
}

void Pista::deserializar (const std::string& s){
	Utilitario utilitario;
	this->numero = utilitario.convertirAEntero( utilitario.separar(s, SEP, 1) );
}
