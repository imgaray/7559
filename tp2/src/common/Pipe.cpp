#include "Pipe.h"

Pipe :: Pipe() : lectura(true), escritura(true) {
	if (pipe ( this->descriptores ) == -1)
		throw("no se pudo crear el pipe");
}

Pipe::~Pipe() {
}

void Pipe :: setearModo ( const PIPE_MODE modo ) {
	if ( modo == LECTURA ) {
		close ( this->descriptores[1] );
		this->escritura = false;

	} else if ( modo == ESCRITURA ) {
		close ( this->descriptores[0] );
		this->lectura = false;
	}
}

ssize_t Pipe::escribir(const void* dato, int datoSize) {
	if ( this->lectura == true ) {
		if (close (this->descriptores[0]) == -1)
			throw("no se pudo cerrar el pipe de lectura al escribir");
		this->lectura = false;
	}

	return write ( this->descriptores[1],dato,datoSize );
}

ssize_t Pipe :: leer ( void* buffer,const int buffSize ) {
	if ( this->escritura == true ) {
		if (close (this->descriptores[1]) == -1)
			throw("no se pudo cerrar el pipe de escritura al leer");
		this->escritura = false;
	}

	return read ( this->descriptores[0],buffer,buffSize );
}

int Pipe :: getFdLectura () const {
	if ( this->lectura == true )
		return this->descriptores[0];
	else
		return -1;
}

int Pipe :: getFdEscritura () const {
	if ( this->escritura == true )
		return this->descriptores[1];
	else
		return -1;
}

void Pipe :: cerrar () {
	if ( this->lectura == true ) {
		if (close (this->descriptores[0]) == -1)
			throw("no se pudo cerrar el fd de lectura");
		this->lectura = false;
	}

	if ( this->escritura == true ) {	
		if (close (this->descriptores[1]) == -1)
			throw("no se pudo cerrar el fd de escritura");
		this->escritura = false;
	}
}
