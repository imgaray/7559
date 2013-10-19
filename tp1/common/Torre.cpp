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
	ArchivoConfiguracion arch(".cnfg");
	Utilitario u;
	std::string basename = "/tmp/fifo_controlador_";
	LOG("iniciando torre");
	int cantidadControles = u.convertirAEntero(arch.obtenerAtributo("controladores"));
	LOG("cantidad de controles" + arch.obtenerAtributo("controladores"));
	while (cantidadControles) {
		LOG("nombre fifo controlador = " + basename + u.convertirAString(cantidadControles));
		FifoEscritura* fifo = new FifoEscritura(basename + u.convertirAString(cantidadControles));
		LOG("por inciar el proceso de resolvedor numero " + u.convertirAString(cantidadControles));
		Process* proc = new Process("controlador/resolvedorPeticiones", cantidadControles);
		LOG("iniciado proceso de resolvedor de peticiones " + u.convertirAString(cantidadControles));
		LOG("por abrir la fifo " + basename + u.convertirAString(cantidadControles));
		fifo->abrir();
		std::pair<FifoEscritura*, Process*> parcito(fifo, proc);
		procesosConsumidores.push_back(parcito);
		LOG("creado el consumidor numero " + u.convertirAString(cantidadControles));
		cantidadControles--;
	}
	LOG("creacion terminada satisfactoriamente");
}

Torre::~Torre() {
	std::vector<std::pair<FifoEscritura*,Process*> >::iterator iter;
	for(iter = procesosConsumidores.begin(); iter != procesosConsumidores.end(); iter++) {
		std::cout << "por cerrar la fifo en torre" << std::endl;
		(*iter).first->cerrar();
		std::cout << "cerrada la fifo en torre" << std::endl;
		std::cout << "por borrar (y esperar) proceso consumidor" << std::endl;
		delete (*iter).second;
		std::cout << "terminado el proceso consumidor" << std::endl;
		delete (*iter).first;
		std::cout << "borrada la fifo de escritura en torre" << std::endl;
	}
}

void Torre::ingresarAvion(Avion& avion) {
	FifoEscritura* fifo = procesosConsumidores[0].first;
	std::string serial = avion.serializar();
	if (fifo->escribir((const void*)serial.c_str(), serial.size()) == -1)
		throw "no se pudo escribir en el fifo correspondiente";

}
