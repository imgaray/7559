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
	colaCompartida.crear("/tmp/memoria_compartida_cola_compartida", 'a');
	consumidor = new Process("/tmp/dispatcherAviones");
	LOG("creacion terminada satisfactoriamente");
}

Torre::~Torre() {
	colaCompartida.leer().cerrar();
	delete consumidor;
}

void Torre::ingresarAvion(Avion& avion) {
	colaCompartida.leer().push(avion);
}
