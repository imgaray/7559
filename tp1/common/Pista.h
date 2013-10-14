#ifndef PISTA_H
#define PISTA_H

#include "IPista.h"
#include "LockFile.h"

class Pista: public IPista {
public:
	Pista();
	virtual ~Pista();
private:
	LockFile* lock;
};

#endif
