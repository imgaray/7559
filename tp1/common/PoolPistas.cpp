/*
 * PoolPistas.cpp
 *
 *  Created on: 31/10/2013
 *      Author: migue
 */

#include "PoolPistas.h"
#include "Utilitario.h"
#include "ArchivoConfiguracion.h"


PoolPistas* PoolPistas::_instancia = NULL;

#define RUTA_MC_PISTAS_LIBRES "/tmp/mc_pistas_libres"

PoolPistas::PoolPistas() :
		_memoria(RUTA_MC_PISTAS_LIBRES, 'a'),
		_lock(RUTA_MC_PISTAS_LIBRES)
		{
	this->inicializar();
}

PoolPistas::~PoolPistas() {
	_memoria.liberar();
}

void PoolPistas::limpiar() {
	_lock.tomarLock();
	for (int i = 0; i < _cantPistas ; i++) {
		pistas[i] = true; // libre
	}
	_lock.liberarLock();
}

PoolPistas& PoolPistas::instancia() {

	if (_instancia == NULL)
		_instancia = new PoolPistas();
	return *_instancia;
}

int PoolPistas::obtenerPistaLibre() {

	bool encontrado = false;
	int nroPista = 0;

	_lock.tomarLock();

	// busca la primera pista libre
	int i = 0;
	while (i < _cantPistas && encontrado == false)  {
		if (pistas[i] == true) {
			encontrado = true;
			pistas[i] = false;
			nroPista = i+1;
		}
		i++;
	}

	_lock.liberarLock();

	if (encontrado == false) {
		throw "No se pudo encontrar pista libre";
	}


	return nroPista;
}

void PoolPistas::inicializar() {
	Utilitario u;
	ArchivoConfiguracion archivo(".cnfg");

	int cantPistas = u.convertirAEntero(archivo.obtenerAtributo("pistas"));

	if (_memoria.crear(cantPistas * sizeof(bool)) != 0)
		throw "Error al crear la MemComp del PoolPistas";

	_cantPistas = cantPistas;

	this->pistas = (bool*) _memoria.datos();
}

void PoolPistas::liberarPista(int nroPista) {

	if (nroPista > _cantPistas || nroPista <= 0)
		throw "Liberando pista incorrecta";

	_lock.tomarLock();
	if (pistas[nroPista-1] == false) {
		pistas[nroPista-1] = true;
	}
	else {
		throw "Error, intentando liberar pista ya libre";
	}
	_lock.liberarLock();
}

void PoolPistas::liberar() {
	if (_instancia != NULL) {
		delete _instancia;
	}
}
