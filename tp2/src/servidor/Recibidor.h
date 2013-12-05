/*
 * Recibidor.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef RECIBIDOR_H_
#define RECIBIDOR_H_

#include "../common/Definiciones.h"
#include "../common/Empaquetador.h"
#include "../common/SemaforoPSX.h"
#include "../common/Process.h"
#include "../common/SocketUDP.h"
#include "SenialFinalizar.h"
#include "ColaDePaquetes.h"

#include "AreaIntercambio.h"

typedef std::vector<Process*> Procesos;

class Recibidor {
public:
	static Recibidor& instancia();
	static bool instanciado();
	static void liberar();

	int comenzar(int pidResolvedor);

	void dejarDeEscuchar();

	virtual ~Recibidor();

private:
	Recibidor();
	Recibidor(const Recibidor& orig);

	int escuchar(Paquete& paq, DirSocket& dir);

	void transmitirAResolvedor();

	void iniciarProcesoCliente(const Empaquetador& emp, const DirSocket& dir);

	Procesos* _procesos;
	Process* _ultimoProceso;

	SocketUDP _receptor;
	SemaforoPSX *_semIntercambio;
	//SemaforoPSX *_semResolvedor;

	ColaDePaquetes _cola;

	AreaIntercambio _areaIntcmb;

	bool _escuchando;

	static Recibidor *_instancia;

	int _pidResolvedor;

	SenialFinalizar _senialFin;
};

#endif /* RECIBIDOR_H_ */
