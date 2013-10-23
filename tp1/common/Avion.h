#ifndef AVION_H
#define AVION_H

#include "Utilitario.h"
#include <string>

enum EstrategiaAvion {
	TIERRA = 0, AIRE = 1
};

class Avion {
public:
	void accionar();
	Avion();
	const char* serializar();
	void deserializar (const std::string& s);
	int determinarPrioridad();
	Avion(const EstrategiaAvion& estrategia);
	Avion(const Avion& avion);
	Avion(const std::string& s);	
	virtual ~Avion();
	bool operator<(const Avion& avion) const;
	EstrategiaAvion getEstrategia();
	
private:
	EstrategiaAvion estrategia;
};

#endif
