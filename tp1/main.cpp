#include "Process.h"
#include <iostream>
#include <string>
#include "Logger.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "GestorPistas.h"
#include "ArchivoConfiguracion.h"
#include "Utilitario.h"
#include "PoolPistas.h"

#define TAG "MAIN PROCESS"

GestorPistas *gestorPistas;


const char* ruta_mc_pistas_libres = "/tmp/mc_pistas_libres";
const char* ruta_sem_pistas = "/tmp/semaforo_pistas";


void inicializarRecursos() {
	mknod("/tmp/cola_prioridad_elementos", 0666, 0);
	mknod("/tmp/semaforo_push_cola_prioridad", 0666, 0);
	mknod("/tmp/semaforo_pop_cola_prioridad", 0666, 0);


	// para el semaforo y la cola compartida del gestor de pistas
	mknod(ruta_mc_pistas_libres, 0666, 0);
	mknod(ruta_sem_pistas, 0666, 0);

	ArchivoConfiguracion archivo(".cnfg");
	Utilitario u;
	int cantPistas = u.convertirAEntero(archivo.obtenerAtributo("pistas"));

	gestorPistas = new GestorPistas(cantPistas);
	gestorPistas->inicializar();
}


void liberarRecursos() {
	unlink("/tmp/cola_prioridad_elementos");
	unlink("/tmp/semaforo_push_cola_prioridad");
	unlink("/tmp/semaforo_pop_cola_prioridad");

	unlink(ruta_mc_pistas_libres);
	unlink(ruta_sem_pistas);
	
	gestorPistas->eliminar();
}

int main(int argc, char** argv) {

	inicializarRecursos();

	Process* generadorAviones = NULL;
	Process* consumerAviones = NULL;
	Logger::instance().clear();
	Logger::instance().info(TAG, "comenzando la simulacion");
	try {
		std::string favion("aviones/avion");
		Logger::instance().info(TAG, "comenzando generador de aviones");
		generadorAviones = new Process(favion);
		Logger::instance().info(TAG, "generador de aviones iniciado");
		std::string fconsumer("torre/consumerAviones");
		Logger::instance().info(TAG, "comenzando consumer de aviones");
		consumerAviones = new Process(fconsumer);
		Logger::instance().info(TAG, "consumer de aviones iniciado");
	} catch(char const* mensaje) {
		//Logger::instance().fatal(TAG, "generador de aviones iniciado");
		std::cout << "Excepcion catcheada en main principal: " << mensaje << std::endl;
	}

	if (generadorAviones != NULL)
		delete generadorAviones;

	if (consumerAviones != NULL)
		delete consumerAviones;

	liberarRecursos();
	
	if (gestorPistas != NULL)
		delete gestorPistas;
	
	Logger::instance().info(TAG, "finalizado correctamente");
	Logger::close();
	
	return 0;
}
