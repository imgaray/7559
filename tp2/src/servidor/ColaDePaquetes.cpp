/*
 * ColaDePaquetes.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "ColaDePaquetes.h"
#include "../common/MemoriaCompartida.h"
#include "../common/Utilitario.h"
#include "../logger/Logger.h"

#define TAG "ColaDePaquetes"

ColaDePaquetes::ColaDePaquetes() : _semSacar(NULL), _semPoner(NULL), _semMemComp(NULL),
	_memoria(NULL), _indices(NULL){

	_semSacar = new SemaforoPSX(SEM_COLA_PAQ_SACAR, 0); // 0, ninguno para sacar
	_semPoner = new SemaforoPSX(SEM_COLA_PAQ_PONER, CANT_PAQ_COLA); // CANT_PAQ_COLA lugares para poner

	_semMemComp = new SemaforoPSX(SEM_MEM_COMP_COLA_PAQ, 1);

	_memoria = new MemCola(MEM_COMP_COLA_PAQ, 'a');
	_indices = new MemIndices(MEM_COMP_COLA_PAQ, 'b');

	_metaPInicio = _memoria->leer().paquetes;
	_metaPFin = _metaPInicio + CANT_PAQ_COLA - 1;

	Logger::instance().debug(TAG, "Instanciando cola.");

}

ColaDePaquetes::~ColaDePaquetes() {

	if (_semSacar != NULL)
		delete _semSacar;

	if (_semPoner != NULL)
		delete _semPoner;

	if (_semMemComp != NULL)
		delete _semMemComp;

	if (_memoria != NULL)
		delete _memoria;

}

void ColaDePaquetes::destruir() {

	Logger::instance().debug(TAG, "Por destruir cola de paquetes.");

	_memoria->liberar();

	if (_memoria != NULL) {
		_memoria->liberar();
		delete _memoria;
		_memoria = NULL;
	}

	if (_semMemComp != NULL) {
		_semMemComp->destruir();
		delete _semMemComp;
		_semMemComp = NULL;
	}

	if (_semSacar) {
		_semSacar->destruir();
		delete _semSacar;
		_semSacar = NULL;
	}

	if (_semPoner != NULL) {
		_semPoner->destruir();
		delete _semPoner;
		_semPoner = NULL;
	}
}


const Paquete ColaDePaquetes::sacar() {

	Logger::instance().debug(TAG, "Intentando sacar paquete de cola.");

	Utilitario u;

	std::string msj = std::string("Valor antes del wait() (Sacar): ") + u.convertirAString(_semSacar->valorActual());
	Logger::instance().debug(TAG,msj);
	_semSacar->wait();
	msj = std::string("Valor despues del wait() (Sacar): ") + u.convertirAString(_semSacar->valorActual());
	Logger::instance().debug(TAG,msj);


	Paquete paq;
	Indices ind;

	Logger::instance().debug(TAG, "Por sacar paquete de cola.");
	_semMemComp->wait();

	ind = _indices->leer();


	// If necesario porque al capturar y tratar una señal se sale del bloqueo del wait() de Sacar.
	if (ind.cantidad > 0) {
		_metaPaq = _metaPInicio + ind.frente;
		ind.frente++;
		ind.cantidad--;

		copiarPaquete( _metaPaq->datos, _buffer);

		ind.frente = ind.frente % CANT_PAQ_COLA;

		_indices->escribir(ind);

		Utilitario u;
		std::string msj = std::string("Se scao un paquete de la cola. Cantidad actual: ") + u.convertirAString(ind.cantidad);
		Logger::instance().debug(TAG, msj);

		_semMemComp->signal();

		_semPoner->signal();

		paq.deserializar((void*)_buffer);

	}
	else {
		_semMemComp->signal();

		paq.definirTipo(0);

		Logger::instance().debug(TAG, "No se saco ningun paquete de la cola");
	}


	return paq;
}

void ColaDePaquetes::insertar(const Paquete& paquete) {

	Logger::instance().debug(TAG, "Intentando poner paquete en la cola.");

	Utilitario u;

	std::string msj = std::string("Valor antes del wait() (Poner): ") + u.convertirAString(_semSacar->valorActual());
	Logger::instance().debug(TAG,msj);
	_semPoner->wait();
	msj = std::string("Valor despues del wait() (Poner): ") + u.convertirAString(_semSacar->valorActual());
	Logger::instance().debug(TAG,msj);

	Logger::instance().debug(TAG,msj);
	Indices ind;


	Logger::instance().debug(TAG, "Por poner paquete en la cola");

	_semMemComp->wait();

	ind = _indices->leer();

	_metaPaq = _metaPInicio + ind.fondo;
	ind.fondo++;
	ind.cantidad++;
	copiarPaquete((char*)paquete.serializar(), _metaPaq->datos);

	ind.fondo = ind.fondo % CANT_PAQ_COLA;

	_indices->escribir(ind);

	msj = std::string("Paquete puesto en la cola. Cantidad actual: ") + u.convertirAString(ind.cantidad);
	Logger::instance().debug(TAG, msj);

	_semMemComp->signal();
	_semSacar->signal();
}

void ColaDePaquetes::copiarPaquete(const char* origen, char* destino) {
	for(int i = 0; i < TAM_MAX_PAQ ; i++)
		destino[i] = origen[i];
}



void ColaDePaquetes::inicializarIndices() {
	Indices inds;
	inds.fondo = 0;
	inds.frente = 0;
	inds.cantidad = 0;
	_semMemComp->wait();
	if (_indices != NULL) {
		_indices->escribir(inds);
	}
	_semMemComp->signal();
}
