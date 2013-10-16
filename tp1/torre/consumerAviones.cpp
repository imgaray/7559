#ifndef TORRE_CONTROL
#define TORRE_CONTROL

#include <string>
#include "FifoLectura.h"
#include "FifoEscritura.h"
#include "Torre.h"
#include <iostream>

int main(int argc, char** argv) {
	
	static const std::string FIFO_GENERADOR = "/tmp/fifo_generador";
	static const std::string FIFO_RESOLVEDOR = "/tmp/fifo_resolvedor";
	
	FifoLectura fifoGen(FIFO_GENERADOR);
	//FifoEscritura fifoRes(FIFO_RESOLVEDOR);
	
	fifoGen.abrir();
	//fifoRes.abrir();
	
	Torre* torre = new Torre();
	
	// probamos con 20 aviones al principio
	int i = 20;
	while(i) {
		char* buffer = new char[32];
		fifoGen.leer(buffer, (ssize_t) 32);
		std::string serializacion = buffer;
		
		std::cout << "RECIBO:" << serializacion << std::endl;
		
		Avion* avioneta = new Avion(serializacion);
		delete buffer;
		i--;
	}
	
	fifoGen.cerrar();
	//fifoRes.cerrar();
	fifoGen.eliminar();
	return 0;
}

#endif
