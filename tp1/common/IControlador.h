#ifndef ICONTROLADOR_H
#define ICONTROLADOR_H

#include "IAvion.h"
#include "IPista.h"

class IControlador {
public:
	virtual void controlar(IAvion* avion, IPista* pista) = 0;

};

#endif
