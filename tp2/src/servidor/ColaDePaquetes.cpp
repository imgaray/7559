/*
 * ColaDePaquetes.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "ColaDePaquetes.h"

ColaDePaquetes::ColaDePaquetes() : _semSacar(NULL), _semPoner(NULL), _semMemComp(NULL),
	_memoria(NULL), _indices(NULL){

	_semSacar = new SemaforoPSX(SEM_COLA_PAQ_SACAR, 0); // 0, ninguno para sacar
	_semPoner = new SemaforoPSX(SEM_COLA_PAQ_PONER, CANT_PAQ_COLA); // CANT_PAQ_COLA lugares para poner

	_semMemComp = new SemaforoPSX(SEM_MEM_COMP_COLA_PAQ, 1);

	_memoria = new MemCola(MEM_COMP_COLA_PAQ, 'a');
	_indices = new MemIndices(MEM_COMP_COLA_PAQ, 'b');

	_metaPInicio = _memoria->leer();
	_metaPFin = _metaPInicio + CANT_PAQ_COLA - 1;
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
	_semSacar->wait();
	Paquete paq;
	Indices ind;


	_semMemComp->wait();

	ind = _indices->leer();
	_metaPaq = _metaPInicio + ind.frente;
	ind.frente++;

	copiarPaquete( _metaPaq->datos, _buffer);

	ind.frente = ind.frente % CANT_PAQ_COLA;

	_indices->escribir(ind);

	_semMemComp->signal();

	_semPoner->signal();

	paq.deserializar((void*)_buffer);

	return paq;
}

void ColaDePaquetes::insertar(const Paquete& paquete) {
	_semPoner->wait();

	Indices ind;

	_semMemComp->wait();

	ind = _indices->leer();

	_metaPaq = _metaPInicio + ind.fondo;
	ind.fondo++;
	copiarPaquete((char*)paquete.serializar(), _metaPaq->datos);

	ind.fondo = ind.fondo % CANT_PAQ_COLA;

	_indices->escribir(ind);


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
	_semMemComp->wait();
	if (_indices != NULL) {
		_indices->escribir(inds);
	}
	_semMemComp->signal();
}
