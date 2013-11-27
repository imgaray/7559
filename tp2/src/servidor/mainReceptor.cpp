#include <iostream>
#include "ReceptorMensajes.h"
#include "../logger/Logger.h"

#define TAG "MAIN_RECEPTOR_MENSAJES"

int main() {
	int retorno;

	Logger::instance().debug(TAG, "Iniciando main de Receptor de Mensajes.");

	{
		ReceptorMensajes& receptor = ReceptorMensajes::instancia();

		retorno = receptor.comenzar();
	}

	ReceptorMensajes::liberar();

	Logger::instance().debug(TAG, "Finalizando Proceso de Receptor de Mensajes.");

	return retorno;
}
