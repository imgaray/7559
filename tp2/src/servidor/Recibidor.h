/*
 * Recibidor.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef RECIBIDOR_H_
#define RECIBIDOR_H_

#include "../common/Definiciones.h"
#include "../common/SemaforoPSX.h"

class Recibidor {
public:

	static Recibidor& instancia();


	int comenzar();

	virtual ~Recibidor();
private:
	Recibidor();
	Recibidor(const Recibidor& orig);

	int escuchar(Paquete& paq, DirSocket& dir);

	void transmitirAResolvedor(const Paquete& paq, const DirSocket& dir);

	void iniciarProcesoCliente(const DirSocket& dir);

	SocketUDP _receptor;
	SemaforoPSX *_semIntercambio;
	SemaforoPSX *_semResolvedor;

	bool _escuchando;

	static Recibidor _instancia;
};

#endif /* RECIBIDOR_H_ */
