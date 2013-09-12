#include "Fifo.h"

namespace Utilities {

	Fifo::Fifo(std::string file) {
		buildFifo(file.c_str());
	}
	
	Fifo::Fifo(const char* file) {
		buildFifo(file);
	}
	
	void Fifo::close() {
		if (fd != -1) close(fd);
		
	}
	
	void Fifo::delete() {
		if (fd != -1) unlink(fd);
	}
	
	Fifo::~Fifo() {
	
	}
	
	void Fifo::push(void* data, unsigned size) {
		if(this->fd == -1){
			this->fd = open(this->nombre, O_WRONLY);
		}
		int result = write (this->fd, (const void *) data, size);
		if (resultado == -1) throw("Fifo error, could not push from fifo");
	}
	
	void Fifo::pull(void* buffer, unsigned buffer_size) {
		if(this->fd == -1){
			this->fd = open(this->name.c_str(), O_RDONLY);
		}
		int resultado = read(this->fd, (void *) buffer, buffer_size);
		if (resultado == -1) throw("Fifo error, could not pull from fifo");
	}
	
	void Fifo::buildFifo(const char* filename) {
		mknod ( nombre,S_IFIFO|0666,0 );
		// se inicializa el descriptor en -1.
		this->fd = -1;
		name = std::string(filename);
	}
};
