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


int determinarConsumidor(int &indice, int cantidadControles){
	indice++;
	if (indice >= cantidadControles) 
		indice = 0;
	return indice;
}

int main(int argc, char** argv) {
	try {
		LOG("iniciando dispatcher");	
		ArchivoConfiguracion arch(".cnfg");
		Utilitario u;
		static const std::string FIFO_CONTROLADOR = "/tmp/fifo_controladorc_";
		
		ColaPrioridadCompartida colaCompartida;
		
		std::vector<std::pair<FifoEscritura*, Process*> > procesosConsumidores;
		int cantidadControles = u.convertirAEntero(arch.obtenerAtributo("controladores"));
		LOG("cantidad de controles " + arch.obtenerAtributo("controladores"));
		
		//Se crean los procesos consumidores
		while (cantidadControles > 0) {
				FifoEscritura* fifoConsumer = new FifoEscritura(FIFO_CONTROLADOR + u.convertirAString(cantidadControles));
				Process* consumidor = new Process("controlador/consumidorPeticiones", cantidadControles);
				LOG("iniciado proceso de consumidor de peticiones " + u.convertirAString(cantidadControles));
				fifoConsumer->abrir();			
				LOG("abierta la fifo " + FIFO_CONTROLADOR + u.convertirAString(cantidadControles));
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
			try {
				Avion avioneta (colaCompartida.pop());
				const char* aux = avioneta.serializar();
				Logger::instance().info(TAG, "avion recibido " + std::string(aux));
				delete[] aux;
				FifoEscritura* fifo = procesosConsumidores[determinarConsumidor(indice, cantidadControles)].first;
				std::string serial = avioneta.serializar();
				Logger::instance().info(TAG, "por despachar el avion " + serial);
				if (fifo->escribir((const void*)serial.c_str(), (ssize_t) 32 ) == -1) {
					Logger::instance().fatal(TAG, "no se pudo escribir en el fifo correspondiente");
					throw "no se pudo escribir en el fifo correspondiente";
				}
			} catch (char const* ex) {
				status = 0;
				Logger::instance().debug(TAG, "cola de prioridad cerrada");
			}
		} while(status != 0);
		
		std::vector<std::pair<FifoEscritura*, Process*> >::iterator iter = procesosConsumidores.begin();
		
		for(; iter != procesosConsumidores.end(); iter++) {
			iter->first->cerrar();
		}
		
		iter = procesosConsumidores.begin();
		for(; iter != procesosConsumidores.end(); iter++) {
			delete iter->second;
			delete iter->first;
		}
		
		Logger::instance().debug(TAG, "Saliendo del Dispatcher");
		
		return 0;
		
	} catch (char const* e) {
		Logger::instance().fatal(TAG, e);
	}
}

#endif
