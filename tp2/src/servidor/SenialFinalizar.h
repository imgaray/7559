/*
 * SenialFinalizar.h
 *
 *  Created on: 25/11/2013
 *      Author: migue
 */

#ifndef SENIALFINALIZAR_H_
#define SENIALFINALIZAR_H_

#include "../common/Senial.h"

class SenialFinalizar : public Senial {
public:
	SenialFinalizar();

	int numeroSenial();

	void operacion();

	virtual ~SenialFinalizar();
};

#endif /* SENIALFINALIZAR_H_ */
