/**
 * Main de Servidor.
 */

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "../common/GestorDeSeniales.h"
#include "../common/Definiciones.h"
#include "../logger/Logger.h"

#include "../common/SemaforoPSX.h"

#include "ColaDePaquetes.h"
#include "Resolvedor.h"
#include "Recibidor.h"


#define TAG "SERVIDOR"


using namespace std;

bool _seguirProcesando = true;

SemaforoPSX** semaforos;
const int canti_sem = 4;


int mainResolvedor();
int mainRecibidor(int pidResolvedor);

void inicializarRecursos();
void liberarRecursos();




/**
 * TODO
 * Cambiar el nombre de este por por el correcto ( main_SS por main)
 */
int main() {

	Logger::instance().debug(TAG, "Inicializando recursos");
	inicializarRecursos();

	int pidResolvedor, pidRecibidor;

	pidResolvedor = fork();

	if (pidResolvedor == 0) {
		Logger::instance().debug(TAG, "Iniciando proceso Resolverdor");
		return mainResolvedor();
	}

	pidRecibidor = fork();

	if (pidRecibidor == 0) {
		Logger::instance().debug(TAG, "Iniciando proceso Recibidor");
		return mainRecibidor(pidRecibidor);
	}

	cout << "Servidor corriendo ..." << endl;

	// Comienzo normal de servidor

	std::string entrada;
	std::string corte = "salir";
	while (entrada != corte) {
		cout << "(Pulse \"salir\" para finalizar ejecucion): ";
		cin >> entrada;
	}

	GestorDeSeniales::instancia().enviarSenialAProceso(pidResolvedor, SIGNUM_FINALIZACION);
	GestorDeSeniales::instancia().enviarSenialAProceso(pidRecibidor, SIGNUM_FINALIZACION);


	Logger::instance().debug(TAG, "Esperando que finalicen procesos.");

	int estado;
	waitpid(pidResolvedor, &estado, 0);
	waitpid(pidRecibidor, &estado, 0);

	cout << "Finalizado." << endl;

	liberarRecursos();

	Logger::instance().debug(TAG, "Recursos liberados.");

	return 0;
}


int mainResolvedor() {
	int retorno;
	{
		Resolvedor& resolvedor = Resolvedor::instanacia();

		retorno = resolvedor.comenzar();
	}

	Resolvedor::liberar();
	return retorno;
}


int mainRecibidor(int pidResolvedor) {
	int retorno;
	{
		Recibidor& recibidor = Recibidor::instancia();

		retorno = recibidor.comenzar(pidResolvedor);
	}

	Recibidor::liberar();
	return retorno;
}


void inicializarRecursos() {

	mknod(MEM_COMP_COLA_PAQ, 0664, 0);
	mknod(MC_INTCMB_RECIBIDOR, 0664, 0);

	mknod(SEM_COLA_PAQ_PONER, 0644 , 0);
	mknod(SEM_COLA_PAQ_SACAR,0664 , 0);

	mknod(SEM_RESOLVEDOR, 0664, 0);
	mknod(SEM_INTERCAMBIO_RYR, 0664 , 0);

	mknod(SEM_MEM_COMP_COLA_PAQ, 0664, 0);
	mknod(SEM_CONFIRMACION_RECEPTOR, 0664, 0);

	semaforos = new SemaforoPSX*[6];

	semaforos[0] = new SemaforoPSX(SEM_COLA_PAQ_PONER, CANT_PAQ_COLA);
	semaforos[0]->inicializar();

	semaforos[1] = new SemaforoPSX(SEM_COLA_PAQ_SACAR, 0);
	semaforos[1]->inicializar();

	semaforos[2] = new SemaforoPSX(SEM_RESOLVEDOR, 1);
	semaforos[2]->inicializar();

	semaforos[3] = new SemaforoPSX(SEM_INTERCAMBIO_RYR, 0);
	semaforos[3]->inicializar();

	semaforos[4] = new SemaforoPSX(SEM_MEM_COMP_COLA_PAQ, 1);
	semaforos[4]->inicializar();

	semaforos[5] = new SemaforoPSX(SEM_CONFIRMACION_RECEPTOR, 0);
	semaforos[5]->inicializar();


	ColaDePaquetes cola;

	cola.inicializarIndices();
}
void liberarRecursos() {
	unlink(MEM_COMP_COLA_PAQ);
	unlink(MC_INTCMB_RECIBIDOR);


	for (int i = 0; i < 5 ; i++) {
		semaforos[i]->destruir();
		delete semaforos[i];
	}

	delete[] semaforos;

	unlink(SEM_COLA_PAQ_PONER);
	unlink(SEM_COLA_PAQ_SACAR);

	unlink(SEM_RESOLVEDOR);
	unlink(SEM_INTERCAMBIO_RYR);

	unlink(SEM_MEM_COMP_COLA_PAQ);
	unlink(SEM_CONFIRMACION_RECEPTOR);
}
