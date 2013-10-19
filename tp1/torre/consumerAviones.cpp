#ifndef TORRE_CONTROL
#define TORRE_CONTROL

#include <string>
#include "FifoLectura.h"
#include "FifoEscritura.h"
#include "Torre.h"
#include <iostream>
#include <sys/types.h>

int main(int argc, char** argv) {
	

	static const std::string FIFO_GENERADOR = "/tmp/fifo_generador";
	
	FifoLectura fifoGen(FIFO_GENERADOR);
	Torre* torre = new Torre();
	fifoGen.abrir();
	ssize_t status = 1;

	do {
		char* buffer = new char[33];
		buffer[32] = '\0';
		status = fifoGen.leer(buffer, (ssize_t) 32);
		if (status > 0) {
			std::string serializacion = buffer;
			//std::cout << "RECIBO:" << serializacion << std::endl;
			Avion* avioneta = new Avion(serializacion);
			torre->ingresarAvion(*avioneta);
			delete avioneta;
		}
		delete buffer;
		
	} while(status > 0);
	fifoGen.cerrar();
	std::cout << "cerrada la fifo del generador" << std::endl;
	fifoGen.eliminar();
	std::cout << "eliminada la fifo del generador" << std::endl;
	delete torre;
	std::cout << "saliendo del scheduler" << std::endl;
	return 0;
}

#endif
