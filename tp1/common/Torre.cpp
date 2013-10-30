#include "Torre.h"
#include "Utilitario.h"
#include "ArchivoConfiguracion.h"
#include <string>
#include <iostream>
#include "Semaforo.h"
#include "Logger.h"
#include "ArchivoConfiguracion.h"
#define TAG "Torre"

#define LOG(X) Logger::instance().info(TAG, X)

Torre::Torre() {
	try {
		colaCompartida.inicializar();
		consumidor = new Process("torre/dispatcherAviones");
		Logger::instance().debug(TAG,"creacion terminada satisfactoriamente");
	} catch (char const* mensaje){
		std::cout << "Excepcion catcheada en constructor de Torre: " << mensaje << std::endl;
	}
}

Torre::~Torre() {
	Logger::instance().debug(TAG, "por cerrar la cola de prioridad");
	colaCompartida.cerrar();
	Logger::instance().debug(TAG, "cola de prioridad cerrada");
	delete consumidor;
}

void Torre::ingresarAvion(Avion& avion) {
	Utilitario u;
	LOG("avion ingresado de prioridad " + u.convertirAString(avion.determinarPrioridad()));
	colaCompartida.push(avion);
}
