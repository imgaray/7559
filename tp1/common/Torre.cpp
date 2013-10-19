#include "Torre.h"
#include "Utilitario.h"
#include "ArchivoConfiguracion.h"
#include <string>
#include <iostream>

Torre::Torre() {
	ArchivoConfiguracion arch(".cnfg");
	Utilitario u;
	std::string basename = "/tmp/fifo_controlador_";
	int cantidadControles = u.convertirAEntero(arch.obtenerAtributo("controladores"));
	while (cantidadControles) {
		std::cout << "nombre fifo controlador = " << basename + u.convertirAString(cantidadControles) << std::endl;
		FifoEscritura* fifo = new FifoEscritura(basename + u.convertirAString(cantidadControles));
		Process* proc = new Process("controlador/resolvedorPeticiones", cantidadControles);
		std::cout << "proceso de resolvedor de peticiones creado " << std::endl;
		fifo->abrir();
		std::pair<FifoEscritura*, Process*> parcito(fifo, proc);
		procesosConsumidores.push_back(parcito);
		cantidadControles--;
	}
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
	if (fifo->escribir((const char*)serial.c_str(), serial.size()) == -1)
		throw "no se pudo escribir en el fifo correspondiente";

}
