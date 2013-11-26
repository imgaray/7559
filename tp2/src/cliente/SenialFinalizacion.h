/*
 * SenialFinalizacion.h
 *
 *  Created on: 26/11/2013
 *      Author: migue
 */

#ifndef SENIALFINALIZACION_H_
#define SENIALFINALIZACION_H_

#include "../common/Senial.h"

class SenialFinalizacion :public Senial {
public:
	SenialFinalizacion();
	virtual ~SenialFinalizacion();

	int numeroSenial();

	void operacion();
};

#endif /* SENIALFINALIZACION_H_ */
