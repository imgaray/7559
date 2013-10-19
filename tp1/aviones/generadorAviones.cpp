#ifndef GENERADOR_AVIONES
#define GENERADOR_AVIONES

#include "FifoEscritura.h"
#include "Avion.h"
#include "FactoryElementos.h"
#include "Logger.h"
#include <iostream>
#include <stdlib.h>
#include "Utilitario.h"
#include "ArchivoConfiguracion.h"

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
	Utilitario u;
	FifoEscritura fifo(FIFO_GENERADOR);
	ArchivoConfiguracion archivo(".cnfg");
	fifo.abrir();
	// probamos con 20 aviones al principio
	int i = u.convertirAEntero(archivo.obtenerAtributo("aviones-tierra"));
	std::cout << "cantidad de aviones = " << i << std::endl;
	while(i) {
		Avion* avioneta = FactoryElementos::instance().crearAvion(generarPrioridad());
		std::string serializacion = avioneta->serializar();
		//std::cout << "SERIALIZO:" << serializacion << std::endl;
		Logger::info (TAG, "Serializo avion" + serializacion);
		
		if (fifo.escribir((const void*)serializacion.c_str(), (ssize_t) 32) == -1)
			break;
		delete avioneta;
		i--;
	}
	std::cout << TAG << "PROCESS OUT" << std::endl;
	fifo.cerrar();
	return 0;
}

#endif
