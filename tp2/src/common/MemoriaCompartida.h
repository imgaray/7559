#ifndef MEMORIACOMPARTIDA2_H_
#define MEMORIACOMPARTIDA2_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <sys/shm.h>

template <class T> class MemoriaCompartida {

private:
	int	shmId;
	T*	ptrDatos;
	int	cantidadProcesosAdosados() const;

public:
	
	MemoriaCompartida ();
	
	void crear ( const std::string& archivo,const char letra );
	
	void liberar ();

	MemoriaCompartida(const std::string& archivo, const char letra);
	
	MemoriaCompartida(const MemoriaCompartida& origen);

	virtual ~MemoriaCompartida ();
	
	MemoriaCompartida<T>& operator=(const MemoriaCompartida& origen);
	
	void escribir(const T& dato);
	
	T leer() const;
};


#endif
