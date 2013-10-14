#ifndef AVION_H
#define AVION_H

#include "IAvion.h"
#include "EstrategiaAvion.h"

class Avion: public IAvion {
public:
	void accionar();
	Avion(EstrategiaAvion* estrategia);
	virtual ~Avion();
private:
	EstrategiaAvion* estrategia;
};

#endif
