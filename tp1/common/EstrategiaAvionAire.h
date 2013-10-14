#ifndef ESTRATEGIAAVIONAIRE_H
#define ESTRATEGIAAVIONAIRE_H

#include "EstrategiaAvion.h"

class EstrategiaAvionAire: public EstrategiaAvion {
public:
	EstrategiaAvionAire();
	virtual ~EstrategiaAvionAire();
	void operar();
};

#endif

