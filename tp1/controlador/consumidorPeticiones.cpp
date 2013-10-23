#ifndef CONSUMIDORMIERDA
#define CONSUMIDORMIERDA

#include "FifoLectura.h"
#include "Avion.h"
#include "Pista.h"
#include "Controlador.h"
#include <iostream>
#include "Logger.h"
#include "Semaforo.h"
#include "Utilitario.h"

#define TAG "consumidorPeticiones"

int main(int argc, char** argv) {
	
	Utilitario u;
	std::string numero(argv[1]);
	static const std::string FIFO_CONTROLADOR = "/tmp/fifo_controladorc_" + numero;

	FifoLectura fifo(FIFO_CONTROLADOR);
	Logger& logger = Logger::instance();
	logger.debug(TAG + numero, "por abrir la fifo numero " + numero);
	fifo.abrir();
	logger.debug(TAG + numero, "abierta  la fifo numero " + numero);
	std::string ruta = FIFO_CONTROLADOR;
	Logger::instance().info(TAG + numero, "ruta de fifo: " + ruta);
	Controlador c(u.convertirAEntero(numero));
	int resultado = 1;
	do {
		char* ptr = new char[32];
		resultado = fifo.leer(ptr, (ssize_t) 32);
		ptr[31] = '\0';
		if (resultado > 0 ) {
			logger.debug(TAG + numero, "resultado de lectura de fifo " + u.convertirAString(resultado));
			std::string serial = ptr;
			logger.debug(TAG + numero, "serializacion " + serial);
			Avion* avioneta = new Avion(serial);
			//Esta pista deberia llegar de uns serializacion
			Pista* pista = new Pista(1);
			c.manejar(avioneta, pista);
			delete avioneta;
			delete pista;
		} else {
			logger.debug(TAG + numero, "leido EOF de la fifo");
		}
		delete ptr;
	} while(resultado > 0);
	try {
		logger.debug(TAG + numero, "cerrando fifo");
		fifo.cerrar();
		logger.debug(TAG + numero, "fifo numero " + numero + " cerrada correctamente");
		logger.debug(TAG + numero, "eliminando fifo");
		fifo.eliminar();
		logger.debug(TAG + numero, "fifo numero " + numero + " eliminada correctamente");
	} catch (char const* mensaje) {
		logger.error(TAG + numero, "excepcion catcheada: " + std::string(mensaje));
	}
	logger.info(TAG + numero, "saliendo del controlador");
	return 0;
}

#endif
