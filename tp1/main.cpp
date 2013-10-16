#include "Process.h"
#include <iostream>

int main(int argc, char** argv) {
	try {
		std::cout << "comenzando simulacion" << std::endl;
		Process generadorAviones("aviones/avion");
		std::cout << "generador de aviones iniciado" << std::endl;
		Process consumerAviones("torre/torr");
		std::cout << "consumer de aviones iniciado" << std::endl;
		generadorAviones.wait();
		std::cout << "generador de aviones detenido" << std::endl;
		consumerAviones.wait();
		std::cout << "consumer de aviones detenido" << std::endl;
	} catch(const char* mensaje) {
		std::cout << "excepcion agarrada! " << mensaje << std::endl;
	}
}
