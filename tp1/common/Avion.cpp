#include "Avion.h"

void Avion::accionar() {
	this->estrategia->operar();
}

Avion::Avion(EstrategiaAvion* estrategia) {
	this->estrategia = estrategia;
}

Avion::~Avion() {
	delete this->estrategia;
}
