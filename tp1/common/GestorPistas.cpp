#include "GestorPistas.h"
#include "Logger.h"
#include <string>
#include "Utilitario.h"

#define TAG "GestorPistas"

GestorPistas::GestorPistas(int cantidadPistas) :
	_cantidadPistas ("/tmp/mc_pistas", 'a'),
	_pistasLibre ("/tmp/semaforo_pistas", 'a'),
	_semPistas ("/tmp/semaforo_pistas", cantidadPistas)
	{
	// guarda el valor en la memComp y en un int, para luego inicializarlo
	_cantPistasInt = cantidadPistas;
}

void GestorPistas::incializar() {

	if (_cantPistasInt == 0) {
		throw "Error al inicializar el gestor de pistas";
	}

	_cantidadPistas.escribir(_cantPistasInt);
	bool* pistasLibres = new bool[_cantPistasInt];

	// seteo todas las pistas como libre
	for (int i = 0; i < _cantPistasInt ; i++)
		pistasLibres[i] = true;

	_pistasLibre.escribir(pistasLibres);

	if (_semPistas.inicializar() != 0)
		throw "Error al inicilizar el semaforo";
}


int GestorPistas::obtenerPista() {
	Logger::instance().debug(TAG,"obteniendo una pista libre" );

	_semPistas.p();

	int cant = _cantidadPistas.leer();
	bool* pistasLibres = _pistasLibre.leer();
	bool encontrado = false;
	int nroPista = 0;

	// busca la primera pista libre
	int i = 0;
	while (i < cant && encontrado == false)  {
		if (pistasLibres[i] == true) {
			encontrado = true;
			nroPista = i+1;
		}
		i++;
	}

	if (encontrado == false) {
		throw "No se puedo encontrar pista libre";
	}
	Utilitario u;

	Logger::instance().debug(TAG,std::string("se obtubo la pista libre nro ") + u.convertirAString(nroPista));

	return nroPista;
}


void GestorPistas::liberarPista(int nroPista) {
	Utilitario u;
	Logger::instance().debug(TAG,std::string("se esta por liberar la pista nro ") + u.convertirAString(nroPista));
	int cant = _cantidadPistas.leer();

	if (nroPista > cant || nroPista <= 0)
		throw "Liberando pista incorrecta";

	bool * pistasLibres = _pistasLibre.leer();

	if (pistasLibres[nroPista+1] == false) {
		pistasLibres[nroPista+1] = true;
		_semPistas.v();
	}
	else {
		throw "Error, intentando liberar pista ya libre";
	}

	Logger::instance().debug(TAG,std::string("se libero la pista nro ") + u.convertirAString(nroPista));
}

void GestorPistas::eliminar() {
	_cantidadPistas.liberar();

	delete _pistasLibre.leer();
	_pistasLibre.escribir(NULL);
	_pistasLibre.liberar();

	_semPistas.eliminar();
}

GestorPistas::~GestorPistas() {

}

