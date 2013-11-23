/*
 * SocketUDP.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "SocketUDP.h"
#include "Paquete.h"

SocketUDP::SocketUDP() {
	_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (_fd == -1) {
		std::string msj = "Error en socket():";
		msj = std::string(strerror(errno));
		throw msj;
	}

	memset((char *)&_direccion, 0, sizeof(_direccion));

}

SocketUDP::SocketUDP(int fd) {

}

int SocketUDP::enlazar(Puerto puerto) {
	memset((char *)&_direccion, 0, sizeof(_direccion));

	_direccion.sin_family = AF_INET;
	_direccion.sin_port = htons(puerto);
	_direccion.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind( _fd, (struct sockaddr *)&_direccion, (socklen_t)sizeof(struct sockaddr)) >= 0 ) {
        _enlazado = true;
        _conectado = true;
    }
    else {
    	std::string msj = "Enlace de Socket fallido en bind():";
        msj += strerror(errno);
    	throw msj;
    }

	return 0;
}

bool SocketUDP::recibir(Paquete& paquete, DirSocket& emisor) {

	unsigned int tamanioDir = sizeof(emisor._dir);
	long int recibidos = 0, recv;
	struct sockaddr* addr = (sockaddr*) &emisor._dir;

	while (recibidos < TAM_MAX_PAQ && recibidos != -1) {

		recv =  recvfrom(_fd, (void*) _buffer, TAM_MAX_PAQ, 0, addr, &tamanioDir);

		if (recv >= 0 ) {
			recibidos += recv;
		}
		else {
			recibidos = -1;
		}
	}

	if (recibidos == TAM_MAX_PAQ) {
		paquete.deserializar((void*) _buffer);
	}

	return (recibidos == TAM_MAX_PAQ);
}

bool SocketUDP::enviar(const Paquete& paquete, const DirSocket& destino) {

	unsigned int tamanioDir = sizeof(destino._dir);
	long int enviados = 0, env;

	char c= 'a';
	//for (int i = 0; i< TAM_MAX_PAQ; i++) {	_buffer[i] = c;	c++;	}

	while (enviados < TAM_MAX_PAQ && enviados != -1) {
		env = sendto(_fd, paquete.serializar() , TAM_MAX_PAQ, 0 , (struct sockaddr *) &destino._dir, tamanioDir);

		if (env >= 0) {
			enviados += env;
		}
		else {
			enviados = -1;
		}
	}

	return (enviados == TAM_MAX_PAQ);
}

const DirSocket SocketUDP::direccionServidor(Puerto puertoServ, const std::string& nombreServ) {
	DirSocket dirServ;
	memset((char *)&dirServ._dir, 0, sizeof(dirServ._dir));

	dirServ._dir.sin_family = AF_INET;
	dirServ._dir.sin_port = htons(puertoServ);

	struct hostent *servidor;

	servidor = gethostbyname(nombreServ.c_str());

	if (servidor == NULL) {
		std::string msj = "Error al obtener servidor: ";
		msj += nombreServ;
		perror(msj.c_str());
		memset((char *)&dirServ._dir, 0, sizeof(dirServ._dir));
	} else {
		//dirServ._dir.sin_addr.s_addr = ((struct in_addr *)(servidor->h_addr))->s_addr;
		dirServ._dir.sin_addr = *(struct in_addr *) (servidor->h_addr);
	}

	return dirServ;
}

SocketUDP::~SocketUDP() {
	if (_fd != -1) {
		close(_fd);
	}
}

