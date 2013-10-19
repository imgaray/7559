#include "Process.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
	Process* generadorAviones = NULL;
	Process* consumerAviones = NULL;
	try {
		std::cout << "comenzando simulacion" << std::endl;
		std::string favion("aviones/avion");
		generadorAviones = new Process(favion);
		std::cout << "generador de aviones iniciado" << std::endl;
		std::string fconsumer("torre/torr");
		consumerAviones = new Process(fconsumer);
		std::cout << "consumer de aviones iniciado" << std::endl;
	} catch(char const* mensaje) {
		std::cout << "excepcion agarrada! " << mensaje << std::endl;
	}
	if (generadorAviones)
		delete generadorAviones;
	if (consumerAviones)
		delete consumerAviones;
}
