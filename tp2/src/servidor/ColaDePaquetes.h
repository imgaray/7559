/*
 * ColaDePaquetes.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef COLADEPAQUETES_H_
#define COLADEPAQUETES_H_

#include "../common/Definiciones.h"
#include "../common/SemaforoPSX.h"
#include "../common/MemoriaCompartida.h"
#include "../common/Paquete.h"

typedef struct {
	char datos[TAM_MAX_PAQ];
} metaPaquete;


typedef struct{
	int frente;
	int fondo;
} Indices;

typedef MemoriaCompartida<metaPaquete[CANT_PAQ_COLA]> MemCola;
typedef MemoriaCompartida<Indices> MemIndices;

class ColaDePaquetes {
public:
	ColaDePaquetes();
	virtual ~ColaDePaquetes();

	const Paquete sacar();
	void insertar(const Paquete& paquete);

	void destruir();

	void inicializarIndices();

private:


	void copiarPaquete(const char* origen, char* destino);

	void recalcularPunteros();

	SemaforoPSX *_semSacar;
	SemaforoPSX *_semPoner;

	SemaforoPSX *_semMemComp;

	MemCola *_memoria;
	MemIndices *_indices;

	char _buffer[TAM_MAX_PAQ];

	metaPaquete *_metaPInicio;
	metaPaquete *_metaPFin;
	metaPaquete *_metaPaq;
};

#endif /* COLADEPAQUETES_H_ */
