#include "LockFile.h"
#include <iostream>

LockFile :: LockFile ( const std::string nombre ) {

	this->nombre = nombre;
	this->fl.l_type = F_WRLCK;
	this->fl.l_whence = SEEK_SET;
	this->fl.l_start = 0;
	this->fl.l_len = 0;
	this->fd = open ( this->nombre.c_str(),O_CREAT|O_WRONLY,0777 );
	if (this->fd == -1)
		throw("imposible abrir el archivo para armar el lock");
}

int LockFile :: tomarLock () {
	this->fl.l_type = F_WRLCK;
	return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int LockFile :: liberarLock () {
	this->fl.l_type = F_UNLCK;
	return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

ssize_t LockFile :: escribir ( const void* buffer,const ssize_t buffsize ) const {
	if (lseek ( this->fd,0,SEEK_END ) == -1)
		throw("no se pudo acceder al fin del archivo para escritura");
	return write ( this->fd,buffer,buffsize );
}

LockFile :: ~LockFile () {
	if (close ( this->fd ) == -1)
		std::cerr << "imposible cerrar el lock" << std::endl;
}
