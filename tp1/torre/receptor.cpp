#ifndef TORRE_CONTROL
#define TORRE_CONTROL

#include <string>
#include "FifoLectura.h"

int main(int argc, char** argv) {
	Torre* torre = new Torre();
	FifoLectura fifo("/tmp/fifo_generador");
	fifo.abrir();
	// probamos con 20 aviones al principio
	int i = 20;
	while(i) {
		char* buffer = new char[16];
		fifo.leer(buffer, (ssize_t) 16);
		std::string serializacion = buffer;
		Avion* avioneta = new Avion(serializacion);
		delete buffer;
	}
	fifo.cerrar();
	fifo.eliminar();
	return 0;
}

#endif
