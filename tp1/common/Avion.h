#ifndef AVION_H
#define AVION_H

#include "EstrategiaAvion.h"
#include "Utilitario.h"
#include <string>

class Avion {
public:
	void accionar();
	const char* serializar();
	void deserializar (const std::string& s);
	int determinarPrioridad();
	Avion(const EstrategiaAvion& estrategia);
	Avion(const Avion& avion);
	Avion(const std::string& s);	
	virtual ~Avion();
	bool operator<(const Avion& avion) const;
private:
	EstrategiaAvion estrategia;
};

#endif
