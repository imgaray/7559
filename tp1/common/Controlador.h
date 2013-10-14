#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "IAvion.h"
#include "IPista.h"
#include "IControlador.h"

class Controlador: public IControlador {
public:
	void manejar(IAvion* avion, IPista* pista); 
	Controlador();
	virtual ~Controlador();
};

#endif
