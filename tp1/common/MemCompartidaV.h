/*
 * MemoriaCompartida.h
 *
 *  Created on: 25/10/2013
 *      Author: migue
 */

#ifndef MEMORIACOMPARTIDA_H_
#define MEMORIACOMPARTIDA_H_

#include <string>
#include <sys/types.h>


class MemCompartidaV {
public:
	MemCompartidaV(const std::string rutaArchivo, char id);

	int crear(int tamanio);

	void* datos();

	int tamanio();

	int liberar();

	virtual ~MemCompartidaV();

private:

	int procesosAdosados();

	void* _datos;

	char _idArch;
	key_t _clave;
	int _shmId;

	bool _creado;
	bool _liberada;
	int _tamMemoria;
	std::string _rutaArch;
};

#endif /* MEMORIACOMPARTIDA_H_ */
