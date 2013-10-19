#ifndef CONSUMIDORMIERDA
#define CONSUMIDORMIERDA

#include "FifoLectura.h"
#include "Avion.h"
#include "Pista.h"
#include "Controlador.h"
#include <iostream>
#include "Logger.h"

#define TAG "consumidorPeticiones"

int main(int argc, char** argv) {
	
	Utilitario u;
	std::string numero(argv[1]);
	static const std::string FIFO_CONTROLADOR = "/tmp/fifo_controladorc_" + numero;

	FifoLectura fifo(FIFO_CONTROLADOR);
	Logger& logger = Logger::instance();
	logger.debug(TAG, "por abrir la fifo numero " + numero);
	fifo.abrir();
	logger.debug(TAG, "abierta  la fifo numero " + numero);
	std::string ruta = FIFO_CONTROLADOR;
	Logger::instance().info(TAG, "ruta de fifo: " + ruta);
	Controlador c(u.convertirAEntero(numero));
	int resultado = 1;
	do {
		char* ptr = new char[33];
		ptr[32] = '\0';
		resultado = fifo.leer(ptr, (ssize_t) 32);
		logger.debug(TAG, "resultado de lectura de fifo " + u.convertirAString(resultado));
		if (resultado > 0 ) {
			std::string serial = ptr;
			logger.debug(TAG, "serializacion " + serial);
			Avion* avioneta = new Avion(serial);
			//Esta pista deberia llegar de uns serializacion
			Pista* pista = new Pista(1);
			c.manejar(avioneta, pista);
			delete avioneta;
			delete pista;
		}
		delete ptr;
	} while(resultado > 0);
	try {
		logger.debug(TAG, "cerrando fifo");
		fifo.cerrar();
		logger.debug(TAG, "fifo numero " + numero + " cerrada correctamente");
		logger.debug(TAG, "eliminando fifo");
		fifo.eliminar();
		logger.debug(TAG, "fifo numero " + numero + " eliminada correctamente");
	} catch (char const* mensaje) {
		logger.error(TAG, "excepcion catcheada: " + std::string(mensaje));
	}
	logger.info(TAG, "saliendo del controlador");
	return 0;
}

#endif
