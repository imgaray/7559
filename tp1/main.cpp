#include "Process.h"
#include <iostream>
#include <string>
#include "Logger.h"

#define TAG "MAIN PROCESS"

int main(int argc, char** argv) {
	Process* generadorAviones = NULL;
	Process* consumerAviones = NULL;
	Logger::instance().clear();
	Logger::instance().info(TAG, "comenzando la simulacion");
	try {
		std::string favion("aviones/avion");
		Logger::instance().info(TAG, "comenzando generador de aviones");
		generadorAviones = new Process(favion);
		Logger::instance().info(TAG, "generador de aviones iniciado");
		std::string fconsumer("torre/torr");
		Logger::instance().info(TAG, "comenzando consumer de aviones");
		consumerAviones = new Process(fconsumer);
		Logger::instance().info(TAG, "consumer de aviones iniciado");
	} catch(char const* mensaje) {
		Logger::instance().fatal(TAG, "generador de aviones iniciado");
	}
	if (generadorAviones)
		delete generadorAviones;
	if (consumerAviones)
		delete consumerAviones;
	Logger::instance().info(TAG, "finalizado correctamente");
	Logger::close();
}
