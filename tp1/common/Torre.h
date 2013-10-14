#ifndef TORRE_H
#define TORRE_H

#include "Avion.h"
#include <queue>
#include "Pipe.h"

class Torre {
public:
	Torre();
	virtual ~Torre();
	void ingresarAvion(Avion& avion);
private:
	Pipe* pipe;
	std::priority_queue<Avion> avion;
};

#endif
