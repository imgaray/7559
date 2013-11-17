/**
 *  Clase paquete encargada de almacenar los mensajes a enviar recibir
 * 
 */

/**
 *	Propuesta de Paquete: 
 * 	2 bytes para el tamanio. (formato Big Endian)
 *  1 bytes para el tipo.
 *  resto datos ( Mensaje, (Conversaciones, cantidad), NombreNuevaConversacion
 * 
 */


#ifndef PAQUETE_H_
#define PAQUETE_H_


#include <string>

#define TAM_MAX_PAQ 512
#define TAM_CABECERA 3

class Paquete {
public:
	Paquete();
	Paquete(const void* spaquete);
	const Paquete& Paquete(const Paquete& orig);
	~Paquete();
	
	Paquete& operator =(const Paquete& orig);

	void definirTipo(int tipo);

	int tipo() const;

	int tamanio() const;
	
	void agregarDatos(const void* datos, int tamanio);
	
	void limpiar();

	const void* serializar() const;
	
	void deserializar(const void* datos);

	const std::string mensaje() const;

	/**
	 * Atributo creado con memoria dinamica, se debe liberar despues de usar
	 */
	char* atributo(int indice) const;

	void agregarAtributo(void* datos, unsigned tamanio);

private:

	void leerCabecera();

	void actualizarCabecera();

	unsigned char _buffer[TAM_MAX_PAQ];
	unsigned long _tamanioReal;
	unsigned long _ultimaPosicion;
	int _tipo;
	std::string _msj;
};


#endif
