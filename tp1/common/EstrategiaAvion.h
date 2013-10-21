#ifndef ESTRATEGIAAVION_H
#define ESTRATEGIAAVION_H

enum PRIORIDAD_AVION {
	TIERRA = 0, AIRE
};

class EstrategiaAvion {
public:
	EstrategiaAvion();
	EstrategiaAvion(const EstrategiaAvion& copia);
	EstrategiaAvion(PRIORIDAD_AVION prioridad);
	int determinarPrioridad();	
	void operar();
	bool operator<(const EstrategiaAvion& otra) const;
	bool operator==(const EstrategiaAvion& otra) const;
	virtual ~EstrategiaAvion();
	EstrategiaAvion& operator=(const EstrategiaAvion& rhs);
	

private:
	PRIORIDAD_AVION prioridad;
};

#endif
