#ifndef CONTROLADOR
#define CONTROLADOR

#include "FifoLectura.h"
#include "Avion.h"
#include <string>
#include "Utilitario.h"
#include "Process.h"
#include "FifoEscritura.h"
#include <iostream>
#include <queue>
#include "../logger/Logger.h"

#define TAG "ResolvedorPeticiones"

int main(int argc, char** argv) {
	
	Utilitario u;
	std::string numero(argv[1]);
	std::cout << "resolvedorPeticiones argv[1] = " << numero << std::endl;
	static const std::string FIFO_RESOLVEDOR = "/tmp/fifo_controlador_" + numero;
	static const std::string FIFO_CONSUMIDOR = "/tmp/fifo_controladorc_" + numero;
	
	std::priority_queue<Avion> prioridadAviones;

	FifoLectura fifo(FIFO_RESOLVEDOR);
	std::cout << "por abrir la fifo en resolvedor peticiones" << std::endl;
	fifo.abrir();
	std::cout << "abierta la fifo en resolvedor peticiones" << std::endl;
	Process consumidor("controlador/consumidorPeticiones", u.convertirAEntero(numero));
	FifoEscritura fifoConsumer(FIFO_CONSUMIDOR);
	fifoConsumer.abrir();
	std::cout << "abierta la fifo del consumer en resolvedor peticiones" << std::endl;
	int resultado = 1;
	do {
		char* ptr = new char[33];
		ptr[32] = '\0';
		resultado = fifo.leer(ptr, (ssize_t) 32);
		std::cout << "leido " << ptr << std::endl;
		if (resultado > 0) {
			Avion avioneta(ptr);
			prioridadAviones.push(avioneta);
			Avion avioneta2 = prioridadAviones.top();
			prioridadAviones.pop();
			resultado = fifoConsumer.escribir(avioneta2.serializar(), (ssize_t) 32) > 0;
		}
		delete ptr;
	} while(resultado > 0);
	Logger::info(TAG, "saliendo del resolvedor de peticiones");
	fifoConsumer.cerrar();
	Logger::info(TAG, "fifo consumer cerrado");
	fifo.cerrar();
	consumidor.wait();
	Logger::info(TAG, "fifo entrada cerrado");
	fifo.eliminar();
	return 0;
}

#endif
