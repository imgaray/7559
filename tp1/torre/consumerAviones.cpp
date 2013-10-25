#ifndef TORRE_CONTROL
#define TORRE_CONTROL

#include <string>
#include "FifoLectura.h"
#include "Torre.h"
#include <iostream>
#include <sys/types.h>
#include "Logger.h"

#define TAG "consumerAviones"

int main(int argc, char** argv) {
	try {

	static const std::string FIFO_GENERADOR = "/tmp/fifo_generador";
	
	FifoLectura fifoGen(FIFO_GENERADOR);
	Torre* torre = new Torre();
	fifoGen.abrir();
	ssize_t status = 1;

	do {
		char* buffer = new char[32];
		status = fifoGen.leer(buffer, (ssize_t) 32);
		buffer[31] = '\0';
		if (status > 0) {
			std::string serializacion = buffer;
			Logger::instance().debug(TAG, "RECIBO:" +serializacion);
			Avion* avioneta = new Avion(serializacion);
			Logger::instance().info(TAG, "avion recibido, procediendo a ingresarlo");
			torre->ingresarAvion(*avioneta);
			delete avioneta;
		} else {
			Logger::instance().debug(TAG, "leido el end of file");
		}
		delete[] buffer;
		
	} while(status > 0);
	fifoGen.cerrar();
	Logger::instance().debug(TAG,"cerrada la fifo del generador");
	fifoGen.eliminar();
	Logger::instance().debug(TAG, "eliminada la fifo del generador");
	delete torre;
	Logger::instance().debug(TAG, "saliendo del scheduler");
	return 0;
	} catch (char const* e) {
		Logger::instance().fatal(TAG, e);
	}
}

#endif
