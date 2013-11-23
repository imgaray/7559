/*
 * SocketUDP.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef SOCKETUDP_H_
#define SOCKETUDP_H_


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>

#include "Paquete.h"

typedef unsigned short int Puerto;

typedef struct  {
	struct sockaddr_in _dir;
} DirSocket;


class SocketUDP {
public:
    /**
     * @brief Constructor para el Socket que recibe el puerto en donde se va a conectar.
     * @param puerto es puerto por donde establecera la conexion el socket.
     */
    explicit SocketUDP();

    /**
     * @brief Destructor virtual de Socket
     */
    virtual ~SocketUDP();

    /**
     * @brief Enlaza el Socket para poder recivir datos
     */
    int enlazar(Puerto puerto);


    const DirSocket direccionServidor(Puerto puertoServ, const std::string& nombreServ);

    /**
     * @brief Envia el paquete atravez del socket, confirmando si fue enviado correctamente.
     * @param mensaje Mensaje con los datos a enviar.
     * @return booleano indicando si envio correctamente el mensaje
     */
    bool enviar(const Paquete& paquete, const DirSocket& destino);

    /**
	 * @brief Se pone en espera a recibir una respuesta.
	 * @param paquete Paquete donde se van a almacenar los datos recibidos.
	 * @return booleano indicando si se recibio correctamente el paquete.
	 */
    bool recibir(Paquete& paquete, DirSocket& emisor);

    /**
     * @brief Cierra la conexion con el huesped.
     */
    void desconectar();

    /**
     * @brief Retorna un bool indicando si el socket se encuentra
     * en estado de conectado.
     * @return booleano indicando que representa el estado "conectado".
     */
    bool conectado();


    int fdAsociado();

    /**
	 * @brief Constructor que recibe un "file descriptor" ya inicializado.
	 * @param fd "File Descriptor" del nuevo socket.
	 */
	explicit SocketUDP(int fd);

private:


    /**
     * @brief Metodo que guarda lo recibido del socket en el string datos.
     * hasta tener un mensaje completo.
     * @param datos string donde se escribiran los datos recibidos.
     * @return booleano indicando si se recibieron bien los datos.
     */
    bool recibirDatos(std::string& datos);

    /**
     * @brief Metodo que guarda lo recibido del socket en el buffer
     * @return booleano indicando si se recibieron bien los datos.
     */
    bool recibirDatos();


    void operator=(const SocketUDP& orig) {}

    /**
     * @brief Metodo privado que inicializa los atributos basicos.
     */
    void inicializar();

    struct timeval _timeout;
    int _fd;
    struct sockaddr_in _direccion;
    Puerto _puerto;
    bool _conectado;
    bool _enlazado;


    // para Paquetes
    char _buffer[TAM_MAX_PAQ];
};

#endif /* SOCKETUDP_H_ */
