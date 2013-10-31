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
#include "GestorPistas.h"

#define TAG "consumidorPeticiones"

int main(int argc, char** argv) {
	try {

	GestorPistas gestor;
	Utilitario u;
	std::string numero(argv[1]);
	static const std::string FIFO_CONTROLADOR = "/tmp/fifo_controladorc_" + numero;

	FifoLectura fifo(FIFO_CONTROLADOR);
	Logger& logger = Logger::instance();
	fifo.abrir();
	logger.debug(TAG + numero, "abierta la fifo numero " + numero);
	std::string ruta = FIFO_CONTROLADOR;
	Controlador c(u.convertirAEntero(numero));
	int resultado = 1;
	do {
		char* ptr = new char[32];
		logger.debug(TAG + numero, "esperando la lectura de la fifo");
		resultado = fifo.leer(ptr, (ssize_t) 32);
		ptr[31] = '\0';
		if (resultado > 0 ) {
			logger.debug(TAG + numero, "resultado de lectura de fifo " + u.convertirAString(resultado));
			std::string serial = ptr;
			Avion* avioneta = new Avion(serial);
			// esta pista se deberia elegir segun algun algoritmo
			//Pista* pista = new Pista(1);

			int nroPista = gestor.obtenerPista();
			std::string mensaje = std::string("Obtenida pista nro: ") + u.convertirAString(nroPista);

			logger.debug(TAG + numero, mensaje.c_str());

			Pista* pista = new Pista(nroPista);
			c.manejar(avioneta, pista);
			delete avioneta;
			delete pista;

			gestor.liberarPista(nroPista);
			mensaje = std::string("Liberada pista nro: ") + u.convertirAString(nroPista);
			logger.debug(TAG + numero, mensaje);


			logger.debug(TAG + numero, "leido EOF de la fifo");

		} else {
			logger.debug(TAG + numero, "leido EOF de la fifo");
		}
		delete[] ptr;
	} while(resultado > 0);
	try {
		fifo.cerrar();
		logger.debug(TAG + numero, "fifo numero " + numero + " cerrada correctamente");
		fifo.eliminar();
		logger.debug(TAG + numero, "fifo numero " + numero + " eliminada correctamente");
	} catch (char const* mensaje) {
		logger.error(TAG + numero, "excepcion catcheada: " + std::string(mensaje));
	}
	logger.info(TAG + numero, "controlador finalizado");
	return 0;
	} catch (const char* e) {
		Logger::instance().fatal(TAG, e);
	}
}

#endif
