#ifndef TORRE_CONTROL
#define TORRE_CONTROL

#include <string>
#include "FifoLectura.h"
#include "Torre.h"
#include <iostream>
#include <sys/types.h>
#include "Logger.h"
#include "Utilitario.h"

#define TAG "consumerAviones"

int main(int argc, char** argv) {
	try {

		static const std::string FIFO_GENERADOR = "/tmp/fifo_generador";
		
		FifoLectura fifoGen(FIFO_GENERADOR);
		Torre* torre = new Torre();
		fifoGen.abrir();
		ssize_t status = 1;
		Utilitario u;
		do {
			char buffer[32];
			status = fifoGen.leer(buffer, (ssize_t) 32);
			buffer[31] = '\0';
			if (status > 0) {
				std::string serializacion = buffer;
				Avion avioneta(serializacion);
				Logger::instance().info(TAG, "avion recibido de prioridad "
						+ u.convertirAString(avioneta.determinarPrioridad())
						+ ", procediendo a ingresarlo");
				torre->ingresarAvion(avioneta);
			} else {
				Logger::instance().debug(TAG, "leido el end of file");
			}
		} while(status > 0);
		
		fifoGen.cerrar();
		Logger::instance().debug(TAG,"cerrada la fifo del generador");
		fifoGen.eliminar();
		Logger::instance().debug(TAG, "eliminada la fifo del generador");
		delete torre;
		Logger::instance().debug(TAG, "saliendo del consumer");
		return 0;
		
	} catch (char const* e) {
		Logger::instance().fatal(TAG, e);
	}
}

#endif
