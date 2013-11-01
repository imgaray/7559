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
	//_memoria.liberar();
}

void PoolPistas::limpiar() {
	_lock.tomarLock();
	_pistas = _memoria.leer();
	for (int i = 0; i < _cantPistas ; i++) {
		//pistas[i] = true; // libre
		_pistas.pista[i] = true;
	}

	_memoria.escribir(_pistas);
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

	//this->pistas = _memoria.leer().pistas;
	this->_pistas = _memoria.leer();

	// busca la primera pista libre
	int i = 0;
	while (i < _cantPistas && encontrado == false)  {
		if (_pistas.pista[i] == true) {
			encontrado = true;
			_pistas.pista[i] = false;
			nroPista = i+1;
		}
		i++;
	}


	_memoria.escribir(_pistas);
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

	if (cantPistas > MAX_PISTAS) {
		std::string msj = "Cantidad de Pistas excede al Maximo.";
		throw msj;
	}


	//se crea sola en el constructor

	//if (_memoria.crear(RUTA_MC_PISTAS_LIBRES, 'a') != 0)
	//	throw "Error al crear la MemComp del PoolPistas";

	_cantPistas = cantPistas;

	//this->pistas = (bool*) _memoria.datos();
}

void PoolPistas::liberarPista(int nroPista) {

	if (nroPista > _cantPistas || nroPista <= 0)
		throw "Liberando pista incorrecta";

	_lock.tomarLock();
	_pistas = _memoria.leer();

	if (_pistas.pista[nroPista-1] == false) {
		_pistas.pista[nroPista-1] = true;
		_memoria.escribir(_pistas);
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
