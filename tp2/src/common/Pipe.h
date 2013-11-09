#ifndef PIPEOLD_H_
#define PIPEOLD_H_

#include <unistd.h>
#include <fcntl.h>

enum PIPE_MODE {
	LECTURA = 0, ESCRITURA
};

class Pipe {

private:
	int descriptores[2];
	bool lectura;
	bool escritura;

public:
	Pipe();
	~Pipe();

	void setearModo ( PIPE_MODE modo );

	ssize_t escribir ( const void* dato, const int datoSize );
	ssize_t leer (void* buffer, const int buffSize);

	int getFdLectura () const;
	int getFdEscritura () const;

	void cerrar ();
};

#endif /* PIPEOLD_H_ */
