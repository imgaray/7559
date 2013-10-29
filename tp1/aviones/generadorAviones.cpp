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
static const std::string FIFO_GENERADOR = "/tmp/fifo_generador";
int avionesTierra, avionesAire, contadorAvionesTierra, contadorAvionesAire;

EstrategiaAvion obtenerRandom(){
	int aux = rand() % 2 ;
	if (aux == 1)
		return AIRE;
	else if (aux == 0)
		return TIERRA;	
}

EstrategiaAvion generarPrioridad(){
	
	EstrategiaAvion resultado = obtenerRandom();
	
	if (resultado == AIRE){
		contadorAvionesAire++;
		//Logger::instance().debug(TAG, " El random devuelve 1");
	}
	else if (resultado == TIERRA) {
		contadorAvionesTierra++;
		//Logger::instance().debug(TAG, " El random devuelve 0");
	}

	if (contadorAvionesAire > avionesAire)
		resultado = TIERRA;
	if (contadorAvionesTierra > avionesTierra)
		resultado = AIRE; 

	return resultado;	
}

int main(int argc, char** argv) {
	try {
		Utilitario u;
		FifoEscritura fifo(FIFO_GENERADOR);
		ArchivoConfiguracion archivo(".cnfg");
		fifo.abrir();
		contadorAvionesTierra = contadorAvionesAire = 0;
		avionesTierra = u.convertirAEntero(archivo.obtenerAtributo("aviones-tierra"));
		avionesAire = u.convertirAEntero(archivo.obtenerAtributo("aviones-aire"));
		int i = avionesTierra + avionesAire;
		Logger::instance().info(TAG, "Por enviar "+ u.convertirAString(i) + " aviones");
		Logger::instance().info(TAG, "Aviones a despegar: "+ u.convertirAString(avionesTierra));
		Logger::instance().info(TAG, "Aviones a aterrizar: "+ u.convertirAString(avionesAire));
		srand (time(0));
		while(i) {
			Avion* avioneta = FactoryElementos::instance().crearAvion(generarPrioridad());
			const char* serializacion = avioneta->serializar();
			Logger::instance().info(TAG, "Avion enviado de prioridad "
					+ u.convertirAString(avioneta->determinarPrioridad()));
			if (fifo.escribir((const void*)serializacion, (ssize_t) 32) == -1) {
				Logger::instance().error(TAG, "no se pudo escribir en fifo");
				break;
			}
			delete[] serializacion;
			delete avioneta;
			i--;
		}
		Logger::instance().debug(TAG, "Por cerrar fifo de escritura");
		fifo.cerrar();
		Logger::instance().info(TAG, "Finalizado correctamente");
		return 0;
	} catch (char const* aux) {
		Logger::instance().fatal(TAG, aux);
	}
}

#endif
