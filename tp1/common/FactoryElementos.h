#ifndef FACTORYELEMENTOS_H
#define FACTORYELEMENTOS_H

#include "IAvion.h"
#include "IControlador.h"
#include "IPista.h"

enum ModoFactory {
NORMAL, DEBUG
};

class FactoryElementos {
public:
	IAvion* crearAvion(int numero);
	IPista* crearPista(int numero);
	IControlador* crearControlador(int numero);
	static FactoryElementos& instance();
	virtual ~FactoryElementos();
	static void setPerfil(ModoFactory modo); 
private:
	FactoryElementos();
	static FactoryElementos* factory;
	
};

#endif
