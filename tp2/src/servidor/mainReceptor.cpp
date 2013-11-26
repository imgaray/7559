#include <iostream>
#include "ReceptorMensajes.h"

int main() {
	int retorno;

	{
		ReceptorMensajes& receptor = ReceptorMensajes::instancia();

		retorno = receptor.comenzar();
	}

	ReceptorMensajes::liberar();

	return retorno;
}
