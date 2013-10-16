#ifndef CONTROLADOR
#define CONTROLADOR

#include "FifoLectura.h"
#include "Avion.h"

int main(int argc, char** argv) {
	
	static const std::string FIFO_RESOLVEDOR = "/tmp/fifo_resolvedor";
	
	FifoLectura fifo(FIFO_RESOLVEDOR);
	
	int resultado = 1;
	do {
		char* ptr = new char[33];
		ptr[32] = '\0';
		resultado = fifo.leer(ptr, (ssize_t) 32);
		if (resultado != 0) {
			std::string serial = ptr;
			Avion* avioneta = new Avion(serial);
			avioneta->accionar();
			delete avioneta;
		}
		delete ptr;
	} while(resultado != 0);
	
	fifo.cerrar();
	fifo.eliminar();
	return 0;
}

#endif
