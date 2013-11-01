#include "GestorPistas.h"
#include "Logger.h"
#include <string>
#include <iostream>
#include "Utilitario.h"
#include "PoolPistas.h"

#define TAG "GestorPistas"

void mostrar(bool* pistas, int cant) {

	std::cout << "Cantidad Pistas: " << cant << std::endl;
	for ( int i = 0 ; i < cant ; i++) {
		std::cout << "Pista " << i <<":";
		if (pistas[i] == true)
			std::cout << "LIBRE";
		else if (pistas[i] == false)
			std::cout << "OCUPADA";
		else
			std::cout << "INDEFINIDO**";

		std::cout << "\t" << std::endl;
	}
	std::cout << std::endl;

}


GestorPistas::GestorPistas(int cantidadPistas) :
	_semPistas ("/tmp/semaforo_pistas", cantidadPistas)
	{
}

void GestorPistas::inicializar() {

//	if (_cantPistasInt == 0) {
//		throw "Error al inicializar el gestor de pistas";
//	}
//
//	_cantidadPistas.escribir(_cantPistasInt);
//	bool* pistasLibres = new bool[_cantPistasInt];
//
//	// seteo todas las pistas como libre
//	for (int i = 0; i < _cantPistasInt ; i++)
//		pistasLibres[i] = true;
//
//	_pistasLibre.escribir(pistasLibres);

	// Se instancia el pool de pistas y se limpia
	PoolPistas::instancia().limpiar();

	if (_semPistas.inicializar() != 0)
		throw "Error al inicilizar el semaforo";

	//std::cout << "Valor inicial del semaforo: " << _semPistas.valorActual() << std::endl;
	this->obtenerPista();
	//std::cout << "Valor actual del semaforo: " << _semPistas.valorActual() << std::endl;
}


int GestorPistas::obtenerPista() {
	Logger::instance().debug(TAG,"obteniendo una pista libre" );

	//std::cout << "Valor actual(obtener) del semaforo: " << _semPistas.valorActual() << std::endl;
	_semPistas.p();
	//std::cout << "Valor actual(ya obtenido) del semaforo: " << _semPistas.valorActual() << std::endl;

	int nroPista = PoolPistas::instancia().obtenerPistaLibre();

//	int cant = _cantidadPistas.leer();
//	bool* pistasLibres = _pistasLibre.leer();
//	bool encontrado = false;
//	int nroPista = 0;
//
//
//	mostrar(pistasLibres, cant);
//
//	// busca la primera pista libre
//	int i = 0;
//	while (i < cant && encontrado == false)  {
//		if (pistasLibres[i] == true) {
//			encontrado = true;
//			pistasLibres[i] = false;
//			nroPista = i+1;
//		}
//		i++;
//	}
//
//	if (encontrado == false) {
//		throw "No se puedo encontrar pista libre";
//	}
//
	Utilitario u;

	Logger::instance().debug(TAG,std::string("se obtubo la pista libre nro ") + u.convertirAString(nroPista));

	//std::cout << "Se obtuvo la pista: " << nroPista << std::endl;

	return nroPista;
}


void GestorPistas::liberarPista(int nroPista) {
	Utilitario u;
	Logger::instance().debug(TAG,std::string("se esta por liberar la pista nro ") + u.convertirAString(nroPista));
	//int cant = _cantidadPistas.leer();

	PoolPistas::instancia().liberarPista(nroPista);
	_semPistas.v();

//	if (nroPista > cant || nroPista <= 0)
//		throw "Liberando pista incorrecta";
//
//	bool * pistasLibres = _pistasLibre.leer();
//
//
//	mostrar(pistasLibres, cant);
//
//	if (pistasLibres[nroPista-1] == false) {
//		pistasLibres[nroPista-1] = true;
//		_semPistas.v();
//	}
//	else {
//		throw "Error, intentando liberar pista ya libre";
//	}

	//std::cout << "Se libero la pista nro: " << nroPista << std::endl;
	Logger::instance().debug(TAG,std::string("se libero la pista nro ") + u.convertirAString(nroPista));
}

void GestorPistas::eliminar() {
	_semPistas.eliminar();
}

GestorPistas::~GestorPistas() {

}

