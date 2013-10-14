#ifndef FACTORYELEMENTOS_H
#define FACTORYELEMENTOS_H

#include "Avion.h"
#include "Controlador.h"
#include "Pista.h"

enum ModoFactory {
NORMAL, DEBUG
};

class FactoryElementos {
public:
	Avion* crearAvion(int numero);
	Pista* crearPista(int numero);
	Controlador* crearControlador(int numero);
	static FactoryElementos& instance();
	virtual ~FactoryElementos();
	static void setPerfil(ModoFactory modo); 
private:
	FactoryElementos();
	static FactoryElementos* factory;
	
};

#endif
