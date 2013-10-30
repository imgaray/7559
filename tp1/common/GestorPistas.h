#ifndef GESTORPISTAS_H_
#define GESTORPISTAS_H_

#include "MemoriaCompartida.h"
#include "Semaforo.h"

class GestorPistas {
public:

	/**
	 * Contructor, solo debe invocarse una vez con la cantidad de pistas
	 * correctas, y luego llamar al metodo inicializar().
	 */
	GestorPistas(int cantidadPistas = 0);

	/**
	 * Metodo debe ser llamado una unica vez
	 */
	void incializar();

	/**
	 * Retorna el numero de pista disponible.
	 * Es bloqueante
	 *
	 * Los Nros de pistas van de 1 a N
	 */
	int obtenerPista();

	/**
	 * Libera una pista por su nro, si ya esta liberada lanza una excepcion.
	 * No es bloqueante.
	 */
	void liberarPista(int nroPista);

	/**
	 * Elimina los recuros del gestor
	 */
	void eliminar();

	virtual ~GestorPistas();
private:

	MemoriaCompartida<int> _cantidadPistas;


	/**
	 * @TODO
	 * Creo que no hay problema entre compartir memoria del Heap entre procesos.
	 * porque esto se instancia una sola vez dinamicamente en un proceso.
	 */
	MemoriaCompartida<bool*> _pistasLibre;


	Semaforo _semPistas;
	int _cantPistasInt;
};

#endif /* GESTORPISTAS_H_ */
