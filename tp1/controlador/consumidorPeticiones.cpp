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
	std::cout << "por abrir la fifo en el consumidorpeticiones" << std::endl;
	fifo.abrir();
	std::cout << "abierta  la fifo en el consumidorpeticiones" << std::endl;
	std::string ruta = FIFO_CONTROLADOR;
	Logger::info(TAG, ruta);
	Controlador c(u.convertirAEntero(numero));
	int resultado = 1;
	do {
		char* ptr = new char[33];
		ptr[32] = '\0';
		resultado = fifo.leer(ptr, (ssize_t) 32);
		if (resultado > 0 ) {
			std::string serial = ptr;
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
		fifo.cerrar();
		fifo.eliminar();
	} catch (char const* mensaje) {
		std::cout << "excepcion catcheada: " << mensaje << std::endl;
	}
	std::cout << "saliendo del controlador" << std::endl;
	return 0;
}

#endif
