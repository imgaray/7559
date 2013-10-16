#include "EstrategiaAvion.h"

EstrategiaAvion::EstrategiaAvion(const EstrategiaAvion& copia) {
	this->prioridad = copia.prioridad;
}

EstrategiaAvion::EstrategiaAvion(PRIORIDAD_AVION prioridad) {
	this->prioridad = prioridad;
}

void EstrategiaAvion::operar() {
	
}

bool EstrategiaAvion::operator<(const EstrategiaAvion& otra) const {
	return this->prioridad < otra.prioridad;
}

EstrategiaAvion::~EstrategiaAvion() {
	
}

EstrategiaAvion& EstrategiaAvion::operator=(const EstrategiaAvion& rhs) {
	this->prioridad = rhs.prioridad;
	return *this;
}