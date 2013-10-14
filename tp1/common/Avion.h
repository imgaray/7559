#ifndef AVION_H
#define AVION_H

#include "EstrategiaAvion.h"

class Avion {
public:
	void accionar();
	Avion(const EstrategiaAvion& estrategia);
	Avion(const Avion& avion);
	virtual ~Avion();
	bool operator<(const Avion& avion) const;
private:
	EstrategiaAvion estrategia;
};

#endif
