/**
 * Main de Servidor.
 */

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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
SemaforoPSX* semResolvedor;
SemaforoPSX* semRecibidor;

const int canti_sem = 4;
ColaDePaquetes* colaPaquetes;


int mainResolvedor();
int mainRecibidor();

void inicializarRecursos();
void liberarRecursos();


int main() {

	try{

	Logger::instance().clear();
	Logger::instance().debug(TAG, "Inicializando recursos");
	inicializarRecursos();

	int pidResolvedor, pidRecibidor;

	pidResolvedor = fork();

	if (pidResolvedor == 0) {
		Logger::instance().debug(TAG, "Iniciando proceso Resolvedor");
		return mainResolvedor();
	}

	pidRecibidor = fork();

	if (pidRecibidor == 0) {
		Logger::instance().debug(TAG, "Iniciando proceso Recibidor");
		return mainRecibidor();
	}

	cout << "Servidor corriendo ..." << endl;

	// Comienzo normal de servidor

	std::string entrada;
	std::string corte = "salir";
	while (entrada != corte) {
		cout << "(Pulse \"salir\" para finalizar ejecucion): ";
		cin >> entrada;
	}

	Logger::instance().debug(TAG, "Enviando señales de finalizacion a procesos (Resolvedor y Recibidor).");

	Logger::instance().debug(TAG, "Esperando que servidor se libere para enviar señal de finalizacion.");
	semResolvedor->wait();
	GestorDeSeniales::instancia().enviarSenialAProceso(pidResolvedor, SIGNUM_FINALIZACION);
	semResolvedor->signal();

	semRecibidor->wait();
	GestorDeSeniales::instancia().enviarSenialAProceso(pidRecibidor, SIGNUM_FINALIZACION);
	semRecibidor->signal();

	Logger::instance().debug(TAG, "Esperando que finalicen procesos.");

	int estado;
	do {
		waitpid(pidResolvedor, &estado, 0);
	}while(WIFEXITED(estado) == false);

	do {
		waitpid(pidRecibidor, &estado, 0);
	} while(WIFEXITED(estado) == false);

	cout << "Finalizado." << endl;

	}
	catch (std::string& e) {
		std::cout << e << std::endl;
	}
	catch (const char* e) {
		std::cout << e << std::endl;
	}

	liberarRecursos();

	Logger::instance().debug(TAG, "Recursos liberados.");
	Logger::close();


	return 0;
}


int mainResolvedor() {
	int retorno;

	try {
		Resolvedor& resolvedor = Resolvedor::instancia();

		retorno = resolvedor.comenzar();
	}
	catch ( std::string& e) {
		std::cout << e << std::endl;
	}
	catch ( const char* e) {
		std::cout << e << std::endl;
	}

	Resolvedor::liberar();
	return retorno;
}


int mainRecibidor() {
	int retorno;
	try
	{
		Recibidor& recibidor = Recibidor::instancia();

		retorno = recibidor.comenzar();
	}
	catch(std::string& e) {
		std::cout << e << std::endl;
	}
	catch ( const char* e) {
		std::cout << e << std::endl;
	}

	Recibidor::liberar();
	return retorno;
}


void inicializarRecursos() {

	if (mknod(MEM_COMP_COLA_PAQ, 0777, 0) == -1)
		std::cout << "Error en mknod: " << MEM_COMP_COLA_PAQ << ": " << strerror(errno) << std::endl;

	if (mknod(MC_INTCMB_RECIBIDOR, 0777, 0) == -1)
		std::cout << "Error en mknod: " << MC_INTCMB_RECIBIDOR << ": " << strerror(errno) << std::endl;

	if (mknod(SEM_COLA_PAQ_PONER, 0777 , 0) == -1)
		std::cout << "Error en mknod: " << SEM_COLA_PAQ_PONER << ": " << strerror(errno) << std::endl;

	if (mknod(SEM_COLA_PAQ_SACAR,0777 , 0) == -1 )
		std::cout << "Error en mknod: " << SEM_COLA_PAQ_SACAR << ": " << strerror(errno) << std::endl;

	if (mknod(SEM_RESOLVEDOR, 0777, 0) == -1)
		std::cout << "Error en mknod: " << SEM_RESOLVEDOR<< ": " << strerror(errno) << std::endl;

	if (mknod(SEM_INTERCAMBIO_RYR, 0777 , 0) == -1)
		std::cout << "Error en mknod: " << SEM_INTERCAMBIO_RYR << ": " << strerror(errno) << std::endl;

	if (mknod(SEM_MEM_COMP_COLA_PAQ, 0777, 0) == -1)
		std::cout << "Error en mknod: " << SEM_MEM_COMP_COLA_PAQ << ": " << strerror(errno) << std::endl;

	if (mknod(SEM_RECIBIDOR, 0777, 0) == -1)
		std::cout << "Error en mknod: " << SEM_RECIBIDOR << ": " << strerror(errno) << std::endl;

	semaforos = new SemaforoPSX*[6];

	semaforos[0] = new SemaforoPSX(SEM_COLA_PAQ_PONER, CANT_PAQ_COLA);
	semaforos[0]->inicializar();

	semaforos[1] = new SemaforoPSX(SEM_COLA_PAQ_SACAR, 0);
	semaforos[1]->inicializar();

	semaforos[2] = new SemaforoPSX(SEM_RESOLVEDOR, 1);
	semaforos[2]->inicializar();
	semResolvedor = semaforos[2];

	semaforos[3] = new SemaforoPSX(SEM_INTERCAMBIO_RYR, 0);
	semaforos[3]->inicializar();

	semaforos[4] = new SemaforoPSX(SEM_MEM_COMP_COLA_PAQ, 1);
	semaforos[4]->inicializar();

	semaforos[5] = new SemaforoPSX(SEM_RECIBIDOR, 1);
	semaforos[5]->inicializar();
	semRecibidor = semaforos[5];


	colaPaquetes = new ColaDePaquetes();
	colaPaquetes->inicializarIndices();
}
void liberarRecursos() {

	delete colaPaquetes;

	unlink(MEM_COMP_COLA_PAQ);
	unlink(MC_INTCMB_RECIBIDOR);

	for (int i = 0; i < 6 ; i++) {
		semaforos[i]->destruir();
		delete semaforos[i];
	}

	delete[] semaforos;

	unlink(SEM_COLA_PAQ_PONER);
	unlink(SEM_COLA_PAQ_SACAR);

	unlink(SEM_RESOLVEDOR);
	unlink(SEM_INTERCAMBIO_RYR);

	unlink(SEM_MEM_COMP_COLA_PAQ);
	unlink(SEM_RECIBIDOR);

}
