#include "Torre.h"
#include "Utilitario.h"
#include "ArchivoConfiguracion.h"
#include <string>
#include <iostream>
#include "Semaforo.h"
#include "Logger.h"
#define TAG "Torre"

#define LOG(X) Logger::instance().info(TAG, X)

Torre::Torre() {
	try {
		consumidor = new Process("torre/dispatcherAviones");
		LOG("creacion terminada satisfactoriamente");
	} catch (char const* mensaje){
		std::cout << "Excepcion catcheada: " << mensaje << std::endl;
	}
}

Torre::~Torre() {
	colaCompartida.cerrar();
	delete consumidor;
}

void Torre::ingresarAvion(Avion& avion) {
	colaCompartida.push(avion);
}
