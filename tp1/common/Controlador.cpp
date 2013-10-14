#include "Controlador.h"

void Controlador::manejar(Avion* avion, Pista* pista) {
	pista->tomar();
	avion->accionar();
	pista->liberar();
}
 
Controlador::Controlador(unsigned numero): numero(numero) {
	
}

Controlador::~Controlador() {
	
}
