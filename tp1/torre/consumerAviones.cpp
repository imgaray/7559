#ifndef TORRE_CONTROL
#define TORRE_CONTROL

#include <string>
#include "FifoLectura.h"
#include "Torre.h"
#include <iostream>

int main(int argc, char** argv) {
	
	static const std::string FIFO_GENERADOR = "/tmp/fifo_generador";
	
	Torre* torre = new Torre();
	FifoLectura fifo(FIFO_GENERADOR);
	fifo.abrir();
	// probamos con 20 aviones al principio
	int i = 20;
	while(i) {
		char* buffer = new char[32];
		fifo.leer(buffer, (ssize_t) 32);
		std::string serializacion = buffer;
		
		std::cout << "RECIBO:" << serializacion << std::endl;
		
		Avion* avioneta = new Avion(serializacion);
		delete buffer;
		i--;
	}
	
	fifo.cerrar();
	fifo.eliminar();
	return 0;
}

#endif
