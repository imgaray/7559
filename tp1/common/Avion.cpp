#include "Avion.h"

void Avion::accionar() {
	this->estrategia.operar();
}

Avion::Avion(const Avion& avion): estrategia(avion.estrategia) {
}


Avion::Avion(const EstrategiaAvion& estrategia): estrategia(estrategia) {
}

Avion::~Avion() {
}

bool Avion::operator<(const Avion& avion) const {
	return this->estrategia < avion.estrategia;
}
