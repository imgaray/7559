#ifndef DISPATCHER
#define DISPATCHER

#include <string>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include "Logger.h"
#include "FifoEscritura.h"
#include "MemoriaCompartida.h"
#include "ColaPrioridadCompartida.h"
#include "ArchivoConfiguracion.h"
#include "Process.h"

#define TAG "dispatcherAviones"
#define LOG(X) Logger::instance().info(TAG, X)

int determinarConsumidor(int indice, int cantidadControles){
	indice++;
	if (indice >= cantidadControles) indice = 0;
	return indice;
}

int main(int argc, char** argv) {
	
	LOG("iniciando dispatcher");	
	ArchivoConfiguracion arch(".cnfg");
	Utilitario u;
	static const std::string FIFO_CONTROLADOR = "/tmp/fifo_controladorc_";
	
	MemoriaCompartida<ColaPrioridadCompartida> colaCompartida;
	colaCompartida.crear("/tmp/memoria_compartida_cola_compartida", 'a');
	
	std::vector<std::pair<FifoEscritura*, Process*> > procesosConsumidores;
	int cantidadControles = u.convertirAEntero(arch.obtenerAtributo("controladores"));
	LOG("cantidad de controles" + arch.obtenerAtributo("controladores"));
	
	//Se crean los procesos consumidores
	while (cantidadControles) {
			LOG("nombre fifo controlador = " + FIFO_CONTROLADOR + u.convertirAString(cantidadControles));
			FifoEscritura* fifoConsumer = new FifoEscritura(FIFO_CONTROLADOR + u.convertirAString(cantidadControles));
			LOG("por inciar el proceso de consumidor numero " + u.convertirAString(cantidadControles));
			Process* consumidor = new Process("controlador/consumidorPeticiones", cantidadControles);
			LOG("iniciado proceso de consumidor de peticiones " + u.convertirAString(cantidadControles));
			LOG("por abrir la fifo " + FIFO_CONTROLADOR + u.convertirAString(cantidadControles));
			fifoConsumer->abrir();			
			std::pair<FifoEscritura*, Process*> parcito(fifoConsumer, consumidor);
			procesosConsumidores.push_back(parcito);
			LOG("creado el consumidor numero " + u.convertirAString(cantidadControles));
			cantidadControles--;
	}
	LOG("creacion terminada satisfactoriamente");
	cantidadControles = u.convertirAEntero(arch.obtenerAtributo("controladores"));
	
	
	//Leo la memoria compartida para despachar los aviones 
	int status = 1;
	int indice = 0;
	do {
		//Avion* avioneta = colaCompartida.leer().pop();
		Avion avioneta (colaCompartida.leer().pop());
		//if (! avioneta){
		//	 status = 0;
		//	 break;
		//}
		FifoEscritura* fifo = procesosConsumidores[determinarConsumidor(indice, cantidadControles)].first;
		std::string serial = avioneta.serializar();
		Logger::instance().info(TAG, "por despachar el avion " + serial);
		if (fifo->escribir((const void*)serial.c_str(), (ssize_t) 32 ) == -1) {
			Logger::instance().fatal(TAG, "no se pudo escribir en el fifo correspondiente");
			throw "no se pudo escribir en el fifo correspondiente";
		}
		//delete avioneta;
	} while(status != 0);
	
	return 0;
}

#endif
