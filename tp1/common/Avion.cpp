#include "Avion.h"
#include <string.h>
#include <iostream>
#include "Logger.h"

#define SEP ';'
#define TAG "Avion"

static char* nameInfo[2] = {"despegar", "aterrizar"};

void Avion::accionar() {
	Logger::instance().info(TAG, "realiza accion " + std::string(nameInfo[estrategia]));
}

Avion::Avion(): estrategia(TIERRA) {
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
	for (; i < 31; i++) {
		*(serial + i) = 'X';
	}
	serial[31] = '\0';
	return serial;
}

void Avion::deserializar (const std::string& s){
	Utilitario utilitario;
	std::string serial = s;
	utilitario.borrarCaracter(serial, 'X');
	Logger::instance().debug(TAG, "serializacion sin padding " + serial);
	Logger::instance().debug(TAG, "tipo obtenido " + utilitario.convertirAEntero(utilitario.separar(serial, SEP, 1)));
	int codEstrategia = utilitario.convertirAEntero( utilitario.separar(serial, SEP, 1) );
	if (codEstrategia == 0)
		this->estrategia = TIERRA;
	else if (codEstrategia == 1)
		this->estrategia = AIRE;

}

int Avion::determinarPrioridad(){
	return this->estrategia;
}

EstrategiaAvion Avion::getEstrategia() {
	return this->estrategia;
}
