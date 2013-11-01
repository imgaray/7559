#include "Pista.h"
#include <string.h>
#include <iostream>
#include "Logger.h"

#define SEP ';'
#define TAG "Pista"

std::string Pista::basenameRutaPista = "/tmp/pista_nro_";

void Pista::tomar() {
	lock->tomarLock();
	Utilitario u;
	Logger::instance().info(TAG,"pista " + u.convertirAString(numero) + " tomada");
}

void Pista::liberar() {
	Utilitario u;
	Logger::instance().info(TAG,"pista " + u.convertirAString(numero) + " liberada");
	lock->liberarLock();
}

Pista::Pista(unsigned numero): numero(numero) {
	Utilitario u;
	std::string rutaPista = basenameRutaPista + u.convertirAString(numero);
	mknod(rutaPista.c_str(), 0666, 0);
	lock = new LockFile(rutaPista);
}

Pista::Pista(const std::string& s) {
	deserializar(s);
}

Pista::~Pista() {
	Utilitario u;
	std::string rutaPista = basenameRutaPista + u.convertirAString(numero);
	unlink(rutaPista.c_str());
	delete lock;
}

const char* Pista::serializar(){
	Utilitario utilitario;
	
	char* serial = new char[32];
	std::stringstream ss;
	std::string out;
	ss << "PISTA" << SEP << utilitario.convertirAString(numero) << SEP << this->lock->getNombre();
	ss >> out;
	int i = 0;
	for (;i < out.size(); i++) {
		serial[i] = out[i];
	}
	
	for (;i < 32; i ++) {
		serial[i] = 'X';
	}
	serial[31] = '\0';
	return serial;
}

void Pista::deserializar (const std::string& s){
	Utilitario utilitario;
	this->numero = utilitario.convertirAEntero( utilitario.separar(s, SEP, 1) );
}
