/*
 * Resolvedor.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef RESOLVEDOR_H_
#define RESOLVEDOR_H_

#include "../common/Definiciones.h"
#include "../common/Empaquetador.h"
#include "../common/SemaforoPSX.h"
#include "SenialIntcmbResolvedor.h"

#include "ColaDePaquetes.h"


class Resolvedor {
public:
	static Resolvedor& instanacia();
	static bool instanciado();
	static void liberar();

	void dejarDeResponder();

	int comenzar();

	const Paquete resolver(const Paquete& origen, Destinatarios& destinos);

	void enviar(const Paquete& paqueteRespuesta, const Destinatarios& destinos);

	const Paquete agregarNuevoUsuario(const NuevoUsuario& info);

	void usarSemaforos(bool usar);

	virtual ~Resolvedor();

private:

	Resolvedor();
	Resolvedor(const Resolvedor& orig);

	const Paquete agregarUsuario(const Paquete& paquete);

	void agregarConversacion(const Paquete& paquete);

	const Paquete crearConversacion(const Empaquetador& empaquetador, Destinatarios& destinos);

	const Paquete unirseConversacion(const Empaquetador& empaquetador, Destinatarios& destinos);

	const Paquete conversaciones(const Empaquetador& emp,Destinatarios& destinos);

	const Paquete reenviarMensaje(const Empaquetador& empaquetador, Destinatarios& destinos);

	const Paquete paqueteNoValido(const Empaquetador& emp, Destinatarios& destinos);

	const Paquete finalizarSesion(const Empaquetador& empaquetador, Destinatarios& destinos);


	void eliminarUsuarioDeConversacion(const IdConversacion& idConv, const IdUsuario& idUsr);

	void agregarDestinos(IdConversacion id, Destinatarios& destinos);

	void enviarPaquete(IdUsuario id, const Paquete& paq);


	void eliminarUsuariosFinalizados();

	void wait();
	void signal();


	Conversaciones _conversaciones;
	ConvUsuarios _usrXConv;
	Usuarios _usuarios;

	UsuariosAEliminar _usrAEliminar;

	SocketUDP _emisor;
	int _ultimoIDLibre;

	SemaforoPSX _semResolvedor;
	bool _usarSemaforo;

	ColaDePaquetes _colaPaquetes;
	bool _seguirEnviando;


	static Resolvedor* _instancia;
};

#endif /* RESOLVEDOR_H_ */
