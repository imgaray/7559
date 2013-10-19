#ifndef GENERADOR_AVIONES
#define GENERADOR_AVIONES

#include "FifoEscritura.h"
#include "Avion.h"
#include "FactoryElementos.h"
#include "Logger.h"
#include <iostream>
#include <cstdlib>
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
	int i = u.convertirAEntero(archivo.obtenerAtributo("aviones-tierra"));
	Logger::instance().info(TAG, "cantidad de aviones = "+ u.convertirAString(i));
	while(i) {
		Avion* avioneta = FactoryElementos::instance().crearAvion(generarPrioridad());
		std::string serializacion = avioneta->serializar();
		Logger::instance().debug(TAG, "Serializo avion " + serializacion);
		
		if (fifo.escribir((const void*)serializacion.c_str(), (ssize_t) 32) == -1) {
			Logger::instance().error(TAG, "no se pudo escribir en fifo");
			break;
		}
		delete avioneta;
		i--;
	}
	Logger::instance().info(TAG, "Por cerrar fifo de escritura");
	fifo.cerrar();
	Logger::instance().info(TAG, "Finalizado correctamente");
	return 0;
}

#endif
