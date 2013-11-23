/*
 * Resolvedor.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef RESOLVEDOR_H_
#define RESOLVEDOR_H_

#include "../common/Paquete.h"
#include "../common/Definiciones.h"



class Resolvedor {
public:
	static Resolvedor& instanacia();

	const Paquete resolver(const Paquete& origen, Destinatarios& destinos);
	void enviar(const Paquete& paqueteRespuesta, const Destinatarios& destinos);
	virtual ~Resolvedor();

private:

	Resolvedor();
	Resolvedor(const Resolvedor& orig);

	const Paquete agregarUsuario(const Paquete& paquete);

	void agregarConversacion(const Paquete& paquete);

	const Paquete crearConversacion(const Empaquetador& empaquetador);


	Conversaciones _conversaciones;
	ConvUsuarios _usrXConv;
	Usuarios _usuarios;

	SocketUDP _emisor;
	int _ultimoIDLibre;


	static Resolvedor _instancia;
};

#endif /* RESOLVEDOR_H_ */
