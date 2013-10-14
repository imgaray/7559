#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "Avion.h"
#include "Pista.h"
#include "Controlador.h"

class Controlador {
public:
	void manejar(Avion* avion, Pista* pista); 
	Controlador(unsigned numero);
	virtual ~Controlador();
private:
	unsigned numero;
};

#endif
