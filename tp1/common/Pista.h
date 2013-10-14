#ifndef PISTA_H
#define PISTA_H

#include "LockFile.h"

class Pista {
public:
	void tomar();
	void liberar();
	Pista();
	virtual ~Pista();
private:
	LockFile* lock;
};

#endif
