#include "Controlador.h"

void Controlador::manejar(IAvion* avion, IPista* pista) {
	pista->tomar();
	avion->accionar();
	pista->liberar();
}
 
Controlador::Controlador() {
	
}

Controlador::~Controlador() {
	
}
