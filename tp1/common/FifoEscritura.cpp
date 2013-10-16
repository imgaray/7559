#include "FifoEscritura.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

FifoEscritura::FifoEscritura(const std::string nombre) : Fifo(nombre) {
}

FifoEscritura::~FifoEscritura() {
}

void FifoEscritura::abrir() {
	fd = open ( nombre.c_str(),O_WRONLY );
	if (fd == -1){
		printf ("Error no is : %d\n", errno);
        printf("Error description is : %s\n",strerror(errno));
		throw("no se pudo abrir el fifo de escritura");
	}
}

ssize_t FifoEscritura::escribir(const void* buffer,const ssize_t buffsize) const {
	return write ( fd,buffer,buffsize );
}
