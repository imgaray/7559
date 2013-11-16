/**
 *  Clase paquete encargada de almacenar los mensajes a enviar recibir
 * 
 */

/**
 *	Propuesta de Paquete: 
 * 	2 bytes para el tamanio.
 *  1 bytes para el tipo.
 *  resto datos ( Mensaje, (Conversaciones, cantidad), NombreNuevaConversacion
 * 
 */


#define TAM_MAX_PAQ 512

class Paquete {
public:
	Paquete();
	Paquete(void* spaquete);
	~Paquete();
	
	enum Tipo {
		MENSAJE,
		FIN_SESION,
		INICIO_SESION,
		CONVERSACIONES,
		CREAR_CONVERSACION
	};

	void definirTipo(Tipo tipo);
	int tamanio();
	
	void agregarDatos(void* datos, int tamanio);
	
	
	void* serializar();
	
	void deserializar(void* datos);
private:
	char* _buffer[TAM_MAX_PAQ];
};
