#include "Fifo.h"

Fifo::Fifo(const std::string nombre) : nombre(nombre), fd(-1) {
	if (mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 ) == -1)
		throw("no se pudo crear el archivo del fifo");
}

Fifo::~Fifo() {
}

void Fifo::cerrar() {
	if (close ( fd ) == -1)
		throw("no se pudo cerrar el fifo");
	fd = -1;
}

void Fifo::eliminar() const {
	if (unlink ( nombre.c_str() ) == -1)
		throw("no se pudo borrar el fifo");
}
