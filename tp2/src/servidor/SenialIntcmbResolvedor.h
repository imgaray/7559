/*
 * SenialIntcmbResolvedor.h
 *
 *  Created on: 25/11/2013
 *      Author: migue
 */

#ifndef SENIALINTCMBRESOLVEDOR_H_
#define SENIALINTCMBRESOLVEDOR_H_

#include "../common/Senial.h"

class SenialIntcmbResolvedor : public Senial {
public:
	SenialIntcmbResolvedor();
	virtual ~SenialIntcmbResolvedor();

	int numeroSenial();

	void operacion();

private:

};

#endif /* SENIALINTCMBRESOLVEDOR_H_ */
