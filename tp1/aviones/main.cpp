#ifndef GENERADOR_AVIONES_H
#define GENERADOR_AVIONES_H

#include "FifoEscritura.h"
#include "Avion.h"
#include "FactoryElementos.h"

int main(int argc, char** argv) {
	FifoEscritura fifo("/tmp/fifo_generador");
	fifo.abrir();
	// probamos con 20 aviones al principio
	int i = 20;
	while(i) {
		Avion* avioneta = FactoryElementos::instance().crearAvion(i);
		std::string serializacion = avioneta->serializar();
		fifo.escribir((const void*)serializacion.c_str(), (ssize_t) serializacion.size());
		delete avioneta;
	}
	fifo.cerrar();
	fifo.eliminar();
	return 0;
}

#endif
