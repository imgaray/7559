#ifndef TORRE_H
#define TORRE_H

#include "Avion.h"
#include "Process.h"
#include "FifoEscritura.h"
#include <utility>
#include <vector>
#include "LockFile.h"

class Torre {
public:
	Torre();
	virtual ~Torre();
	void ingresarAvion(Avion& avion);
private:
	std::vector<std::pair<FifoEscritura*, Process*> > procesosConsumidores;
};

#endif
