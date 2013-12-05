
/**
 * Tipos de Paquetes (formatos y sus datos)
 *
 *
 * TAM || MENSAJE || NombreUsuario || "mesaje"
 *
 * TAM || FIN_SESION || nombreUsuario
 *
 * TAM || INICIO_SESION || nombreUsuario
 *
 * TAM || CONVERSACIONES || Nombre de Conversacion								(SOLICITUD)
 * TAM || CONVERSACIONES || #Listado de Conversaciones (tamString || nombre)	(RESPUESTA)
 *
 * TAM || CREAR_CONVERSACION || nombreUSuario || NombreNuevaConversacion
 *
 * TAM || UNIRSE_CONVERSACION || nombreUsuario || NombreConversacion
 *
 * TAM || ERROR || "Mensaje de Error"
 *
 * TAM || OK || [ Mensaje, opcional ]
 *
 */

/**
 * Nuevos tipos de paquetes.
 *
 * TAM || PROTO_INICIO_SESION || 1 || (struct de nuevo Usuario
 *
 * TAM || USUARIOS_CONVERSACION || 2 || Nombre Usuario | Nombre de Conversacion	 (SOLICITUD)
 * TAM || USUARIOS_CONVERSACION || N || Nombre de Conversacion || # Usuarios(tamString || string)	 (Respuesta)
 */

/**
 * Se debe utilizar siempre esta clase para crear y modificar paquetes.
 */



#ifndef EMPAQUETADOR_H_
#define EMPAQUETADOR_H_


#include "Paquete.h"
#include "Definiciones.h"
#include <vector>



class Empaquetador {
public:
	Empaquetador();
	Empaquetador(const Paquete& paquete);
	virtual ~Empaquetador();

	void asociar(const Paquete& paquete);

	enum TipoPaquete {
			DESCONOCIDO = 0,

			PROTO_INICIO_SESION,
			INICIO_SESION,
			FIN_SESION,

			MENSAJE,

			CREAR_CONVERSACION,
			UNIRSE_CONVERSACION,

			CONVERSACIONES,

			USUARIOS_CONVERSACION,

			OK,
			ERROR
		};


	/*****************************************************************************
	 * Metodos que utilizara el emisor
	 *****************************************************************************/

	void protoInicio(const NuevoUsuario& nuevoUsr);

	/**
	 * Define el paquete como inicio de sesion, adjuntando el nombre del usuario que inicia.
	 */
	void iniciarSesion(const std::string& nombreUsuario);

	/**
	 * Define el paquete de finalizacion de sesion.
	 */
	void finalizarSesion(const std::string& nombreUsuario);

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
	void crearConversacion(const std::string& nomUsuario,const std::string& nombreNuevaConversacion);

	void usuariosEnConversacion(const std::string& nomUsuario, const std::string& nombreConversacion);

	/**
	 * Define el paquete como una respuesta de confirmacion (OK)
	 */
	void confirmarRespuesta();

	/**
	 * Define el paquete como una respuesta de confirmacion (OK) y agrega una mensaje.
	 */
	void confirmarRespuesta(const std::string& mensaje);

	/**
	 * Se intena a unir a la conversacion definida con el nombre
	 */
	void unirseConversacion(const std::string& nomUsario, const std::string& nombreConversacion);


	void verConversaciones(const std::string& nombreUsuario);


	/*************************************************************************
	 * Metodos que usar el receptor
	 *************************************************************************/
	/**
	 * Retorna el mensaje que posee el paquete.
	 */
	const std::string PAQ_mensajeDeUsuario() const;

	/**
	* Retorna el nombre de usuario que posee el paquete, si es Paquete es de Tipo INICIO_SESION o MENSAJE.
	* Caso contrario retorna string vacio.
	*/
	const std::string PAQ_nombreDeUsuario() const;

	/**
	 * Retorna un string con el nombre de la nueva conversacion a crear o la conversacion a la cual se desea unirse.
	 */
	const std::string PAQ_nombreConversacion() const;

	/**
	 * Retorna un std::vector con el nombres de las conversaciones disponibles si el paquete es de tipo
	 * CONVERSACIONES, en caso contrario retorna un contenedor vacio.
	 */
	const std::vector<std::string> PAQ_conversaciones() const;

	/**
	 * Retorna un bool indicando si el paquete es de inicio de sesion.
	 */
	bool PAQ_iniciandoSesion() const;

	/**
	 * Retorna un bool indicando si el paquete es de finalizacion de sesion.
	 */
	bool PAQ_finalizandoSesion() const;

	/**
	 * Retorna un bool indicando si el paquete es de confirmacion.
	 */
	bool PAQ_confirmacionRecibida() const;

	/**
	 * Retorna un bool indicando si el paquete posee un error.
	 */
	bool PAQ_errorRecibido() const;


	/**
	 * Retorna un bool indicando si el paquete posee un error.
	 */
	const std::string PAQ_mensajeDeError() const;


	const std::vector<std::string> PAQ_usuariosEnConversacion() const;


	void PAQ_protoInicio(NuevoUsuario& nuevoUsr) const;

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
