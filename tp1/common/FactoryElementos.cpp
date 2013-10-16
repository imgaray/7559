#include "FactoryElementos.h"

FactoryElementos* FactoryElementos::factory = NULL;

FactoryElementos::FactoryElementos() {
}

Avion* FactoryElementos::crearAvion(int numero) {
	EstrategiaAvion estrat(TIERRA);
	return new Avion(estrat);
}

Pista* FactoryElementos::crearPista(int numero) {
	return NULL;
}

Controlador* FactoryElementos::crearControlador(int numero) {
	return NULL;
}

FactoryElementos& FactoryElementos::instance() {
	if (factory == NULL)
		factory = new FactoryElementos();
	return *factory;
}

FactoryElementos::~FactoryElementos() {
}

static void setPerfil(ModoFactory modo) {

}