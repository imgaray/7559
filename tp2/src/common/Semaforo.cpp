#include "Semaforo.h"

Semaforo :: Semaforo ( const std::string& nombre,const int valorInicial ):valorInicial(valorInicial) {
	int provisoria = ftok ( nombre.c_str(),'a' );
	if (provisoria == -1 )
		throw "no se pudo crear la clave para el semaforo";
	key_t clave = provisoria;
	int provid = semget ( clave,1,0666 | IPC_CREAT );
	if (provid == -1)
		throw "no se pudo obtener el semaforo";
	id = provid;

}

Semaforo::~Semaforo() {
}

int Semaforo :: inicializar () const {

	union semnum {
		int val;
		struct semid_ds* buf;
		ushort* array;
	};

	semnum init;
	init.val = this->valorInicial;
	int resultado = semctl ( this->id,0,SETVAL,init );
	if (resultado == -1)
		throw "no se pudo inicializar el semaforo";
	return resultado;
}

int Semaforo :: p () const {

	struct sembuf operacion;

	operacion.sem_num = 0;	// numero de semaforo
	operacion.sem_op  = -1;	// restar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
	return resultado;
}

int Semaforo :: v () const {

	struct sembuf operacion;

	operacion.sem_num = 0;	// numero de semaforo
	operacion.sem_op  = 1;	// sumar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
	return resultado;
}

void Semaforo :: eliminar () const {
	if (semctl ( this->id,0,IPC_RMID ) == -1)
		throw "no se pudo eliminar el semaforo";
}

int Semaforo :: valorActual() const {
	int resultado = semctl ( this->id,0,GETVAL);

	return resultado;
}
