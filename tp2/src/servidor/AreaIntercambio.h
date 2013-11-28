/*
 * AreaIntercambio.h
 *
 *  Created on: 25/11/2013
 *      Author: migue
 */

#ifndef AREAINTERCAMBIO_H_
#define AREAINTERCAMBIO_H_

#include "../common/MemoriaCompartida.h"
#include "../common/Definiciones.h"


class AreaIntercambio {
public:
	AreaIntercambio();

	const NuevoUsuario leer();
	void escribir(const NuevoUsuario& info);

	void destruir();

	virtual ~AreaIntercambio();
private:
	MemoriaCompartida<NuevoUsuario> *_memComp;
};

#endif /* AREAINTERCAMBIO_H_ */
