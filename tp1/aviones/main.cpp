#ifndef GENERADOR_AVIONES_H
#define GENERADOR_AVIONES_H

#include "FifoEscritura.h"
#include "Avion.h"
#include "FactoryElementos.h"
#include <iostream>

int main(int argc, char** argv) {
	
	static const std::string FIFO_GENERADOR = "/tmp/fifo_generador";
	
	FifoEscritura fifo(FIFO_GENERADOR);
	fifo.abrir();
	// probamos con 20 aviones al principio
	int i = 20;
	while(i) {
		Avion* avioneta = FactoryElementos::instance().crearAvion(i);
		std::string serializacion = avioneta->serializar();
		
		std::cout << "SERIALIZO:" << serializacion << std::endl;
		
		//fifo.escribir((const void*)serializacion.c_str(), (ssize_t) serializacion.size());
		fifo.escribir((const void*)serializacion.c_str(), (ssize_t) 32);
		delete avioneta;
		i--;
	}
	
	fifo.cerrar();
	return 0;
}

#endif
