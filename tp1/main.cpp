#include "Process.h"
#include <iostream>
#include <string>
#include "Logger.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TAG "MAIN PROCESS"

int main(int argc, char** argv) {
	mknod("/tmp/cola_prioridad_elementos", 0666, 0);
	mknod("/tmp/semaforo_push_cola_prioridad", 0666, 0);
	mknod("/tmp/semaforo_pop_cola_prioridad", 0666, 0);
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
	wait(NULL);
	if (generadorAviones)
		delete generadorAviones;
	if (consumerAviones)
		delete consumerAviones;
	unlink("/tmp/cola_prioridad_elementos");
	unlink("/tmp/semaforo_push_cola_prioridad");
	unlink("/tmp/semaforo_pop_cola_prioridad");
	Logger::instance().info(TAG, "finalizado correctamente");
	Logger::close();
	
	return 0;
}
