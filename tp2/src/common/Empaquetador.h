
/**
 * Tipos de Paquetes (formatos y sus datos)
 *
 *
 * TAM || MENSAJE || "mesaje"
 *
 * TAM || FIN_SESION
 *
 * TAM || INICIO_SESION || NombreUsuario
 *
 * TAM || CONVERSACIONES || #Listado de Conversaciones (tamString || nombre)
 *
 * TAM || CREAR_CONVERSACION || NombreNuevaConversacion
 *
 * TAM || UNIRSE_CONVERSACION || NombreConversacion
 *
 * TAM || ERROR || "Mensaje de Error"
 *
 * TAM || OK || [ Mensaje, opcional ]
 *
 */


/**
 * Se debe utilizar siempre esta clase para crear y modificar paquetes.
 */



#ifndef EMPAQUETADOR_H_
#define EMPAQUETADOR_H_


#include "Paquete.h"
#include <vector>



class Empaquetador {
public:
	Empaquetador();
	Empaquetador(const Paquete& paquete);
	virtual ~Empaquetador();

	void asociar(const Paquete& paquete);

	enum TipoPaquete {
			DESCONOCIDO = 0,

			INICIO_SESION,
			FIN_SESION,

			MENSAJE,

			CREAR_CONVERSACION,
			UNIRSE_CONVERSACION,

			CONVERSACIONES,

			OK,
			ERROR
		};


	/*****************************************************************************
	 * Metodos que utilizara el emisor
	 *****************************************************************************/

	/**
	 * Define el paquete como inicio de sesion, adjuntando el nombre del usuario que inicia.
	 */
	void iniciarSesion(const std::string& nombreUsuario);

	/**
	 * Define el paquete de finalizacion de sesion.
	 */
	void finalizarSesion();

	/**
	 * Agrega un vector de convesarciones al paquete y lo define como tipo CONVERSACIONES
	 */
	void agregarConversaciones(std::vector<std::string> conversaciones);

	/**
	 * Agrega un mensaje al paquete y lo define como MENSAJE
	 */
	void agregarMensaje(const std::string& nombreUsuario, const std::string& mensaje);

	/**
	 * Agrega un Mensaje de Error y define el paquete como error.
	 */
	void agregarMensajeError(const std::string& mensaje);

	/**
	 * Agrega un nombre de conversacion al paquete y lo define con el tipo de CREAR_CONVERSACION
	 */
	void crearConversacion(std::string& nombreNuevaConversacion);

	/**
	 * Define el paquete como una respuesta de confirmacion (OK)
	 */
	void confirmarRespuesta();

	/*************************************************************************
	 * Metodos que usar el receptor
	 *************************************************************************/
	/**
	 * Retorna el mensaje que posee el paquete.
	 */
	const std::string mensajeDeUsuario() const;

	/**
	* Retorna el nombre de usuario que posee el paquete, si es Paquete es de Tipo INICIO_SESION o MENSAJE.
	* Caso contrario retorna string vacio.
	*/
	const std::string nombreDeUsuario() const;

	/**
	 * Retorna un string con el nombre de la nueva conversacion a crear.
	 */
	const std::string nombreConversacion() const;

	/**
	 * Retorna un std::vector con el nombres de las conversaciones disponibles si el paquete es de tipo
	 * CONVERSACIONES, en caso contrario retorna un contenedor vacio.
	 */
	const std::vector<std::string> conversaciones() const;

	/**
	 * Retorna un bool indicando si el paquete es de inicio de sesion.
	 */
	bool iniciandoSesion() const;

	/**
	 * Retorna un bool indicando si el paquete es de finalizacion de sesion.
	 */
	bool finalizandoSesion() const;

	/**
	 * Retorna un bool indicando si el paquete es de confirmacion.
	 */
	bool confirmacionRecibida() const;

	/**
	 * Retorna un bool indicando si el paquete posee un error.
	 */
	bool errorRecibido() const;

	/***************************************************************************/

	/**
	 * Retorna el tipo de paquete actual
	 */
	TipoPaquete tipoActual() const;

	/**
	 * Retorna el paquete creado
	 */
	const Paquete& paquete() const;

	/**
	 * Deja el paquete contenido dentro en un estado inicial.
	 */
	void limpiar();

private:
	Paquete _paquete;
};

#endif /* EMPAQUETADOR_H_ */
