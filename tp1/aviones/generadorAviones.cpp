#ifndef GENERADOR_AVIONES
#define GENERADOR_AVIONES

#include "FifoEscritura.h"
#include "Avion.h"
#include "FactoryElementos.h"
#include "Logger.h"
#include <iostream>
#include <stdlib.h>

const string TAG = "generadorAviones";

PRIORIDAD_AVION generarPrioridad(){
	int aux = (rand() % 2) ;
	if (aux == 1)
		return AIRE;
	else if (aux == 0)
		return TIERRA;	
}

int main(int argc, char** argv) {
	
	static const std::string FIFO_GENERADOR = "/tmp/fifo_generador";
	
	FifoEscritura fifo(FIFO_GENERADOR);
	fifo.abrir();
	// probamos con 20 aviones al principio
	int i = 20;
	while(i) {
		Avion* avioneta = FactoryElementos::instance().crearAvion(generarPrioridad());
		std::string serializacion = avioneta->serializar();
		
		std::cout << "SERIALIZO:" << serializacion << std::endl;
		Logger::info (TAG, "Serializo avion" + serializacion);
		
		fifo.escribir((const void*)serializacion.c_str(), (ssize_t) 32);
		delete avioneta;
		i--;
		sleep();
	}
	
	fifo.cerrar();
	return 0;
}

#endif
