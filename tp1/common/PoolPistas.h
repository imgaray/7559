/*
 * PoolPistas.h
 *
 *  Created on: 31/10/2013
 *      Author: migue
 */

#ifndef POOLPISTAS_H_
#define POOLPISTAS_H_

#include "MemoriaCompartida.h"
#include "LockFile.h"

#define MAX_PISTAS 500

class PoolPistas {
public:
	static PoolPistas& instancia();
	/**
	 * Libera los recursos usados
	 */
	static void liberar();

	/**
	 * Retorna un numero de pista libre
	 */
	int obtenerPistaLibre();

	/**
	 * Libera una pista. Lanza excepcion si la pista
	 */
	void liberarPista(int nroPista);

	/**
	 * Establece los valores por defecto (Todas las pistas libres).
	 * Debe llamarse en algun momento. (En el proceso Main)
	 */
	void limpiar();

	virtual ~PoolPistas();
private:

	typedef struct  {
		bool pista[MAX_PISTAS];
	} Capacidad;

	void inicializar();

	PoolPistas();
	static PoolPistas* _instancia;

	LockFile _lock;
	//MemCompartidaV _memoria;
	MemoriaCompartida<Capacidad> _memoria;
	int _cantPistas;
	//bool* pistas;

	Capacidad _pistas;

	std::string _rutaArch;
	char _idArch;
};

#endif /* POOLPISTAS_H_ */
