/**
 * Main de Servidor.
 */

#include <iostream>

#include "../common/GestorDeSeniales.h"


#include "Resolvedor.h"
#include "Recibidor.h"

using namespace std;

bool _seguirProcesando = true;

int mainResolvedor();
int mainRecibidor(int pidResolvedor);


/**
 * TODO
 * Cambiar el nombre de este por por el correcto ( main_SS por main)
 */
int main() {
	int pidResolvedor, pidRecibidor;

	pidResolvedor = fork();

	if (pidResolvedor == 0) {
		return mainResolvedor();
	}

	pidRecibidor = fork();

	if (pidRecibidor == 0) {
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

	int estado;
	waitpid(pidResolvedor, &estado, 0);
	waitpid(pidRecibidor, &estado, 0);

	cout << "Finalizado." << endl;

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
