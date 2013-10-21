#ifndef CONTROLADOR
#define CONTROLADOR

#include "FifoLectura.h"
#include "Avion.h"
#include <string>
#include "Utilitario.h"
#include "Process.h"
#include "FifoEscritura.h"
#include <iostream>
#include <queue>
#include "Logger.h"

#define TAG "ResolvedorPeticiones"

#define LOG(X) Logger::instance().debug(TAG + numero, X)

int main(int argc, char** argv) {
	
	Utilitario u;
	std::string numero(argv[1]);
	LOG("resolvedorPeticiones argv[1] = " + numero);
	static const std::string FIFO_RESOLVEDOR = "/tmp/fifo_controlador_" + numero;
	static const std::string FIFO_CONSUMIDOR = "/tmp/fifo_controladorc_" + numero;
	
	std::priority_queue<Avion> prioridadAviones;
	LOG("por lanzar el consumidor " + numero);
	Process consumidor("controlador/consumidorPeticiones", u.convertirAEntero(numero));
	LOG("consumidor "+numero+" iniciado");
	LOG("Por abrir fifo consumer " + numero);
	FifoEscritura fifoConsumer(FIFO_CONSUMIDOR);
	fifoConsumer.abrir();
	LOG("abierta la fifo del consumer " + numero);
	int resultado = 1;
	FifoLectura fifo(FIFO_RESOLVEDOR);
	LOG("por abrir la fifo lectura " + numero);
	fifo.abrir();
	LOG("abierta la fifo en resolvedor peticiones " + numero);
	do {
		char* ptr = new char[32];
		resultado = fifo.leer(ptr, (ssize_t) 32);
		ptr[31] = '\0';
		if (resultado > 0) {
			LOG("leido " + std::string(ptr));
			Avion avioneta(ptr);
			prioridadAviones.push(avioneta);
			Avion avioneta2 = prioridadAviones.top();
			prioridadAviones.pop();
			const char* serial = avioneta2.serializar();
			LOG("por recepcionar " + std::string(serial));
			resultado &= fifoConsumer.escribir(serial, (ssize_t) 32) > 0;
			delete[] serial;
		} else {
			LOG("leido EOF del resolvedor");
		}
		delete ptr;
	} while(resultado > 0);
	while(prioridadAviones.size() > 0) {
		Avion avioneta2 = prioridadAviones.top();
		prioridadAviones.pop();
		const char* serial = avioneta2.serializar();
		LOG("por recepcionar " + std::string(serial));
		resultado &= fifoConsumer.escribir(serial, (ssize_t) 32) > 0;
		delete[] serial;
	}
	Logger::instance().info(TAG + numero, "saliendo del resolvedor de peticiones");
	fifoConsumer.cerrar();
	Logger::instance().info(TAG + numero, "fifo consumer cerrado");
	fifo.cerrar();
	consumidor.wait();
	Logger::instance().info(TAG + numero, "fifo entrada cerrado");
	fifo.eliminar();
	return 0;
}

#endif
