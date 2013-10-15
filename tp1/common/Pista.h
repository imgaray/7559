#ifndef PISTA_H
#define PISTA_H

#include "LockFile.h"
#include "Utilitario.h"
#include <string>

class Pista {
public:
	void tomar();
	void liberar();
	std::string serializar();
	void deserializar (const std::string& s);
	Pista(unsigned numero);
	Pista(const std::string& s);
	virtual ~Pista();
private:
	LockFile* lock;
	unsigned numero;
};

#endif
