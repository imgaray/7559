/* 
 * File:   Socket.h
 * Author: migue
 *
 * Created on 26 de abril de 2012, 13:15
 */

#ifndef SOCKET_H
#define	SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>

#include "Paquete.h"

//#include "Definiciones.h"

typedef unsigned short int Puerto;

//class Mensaje;

class Paquete; // clase que sustituye a mensaje

class Consulta;
class Respuesta;

/**
 * @class Socket
 * Esta clase es la encarga de la comunicacion entre las distintas
 * partes como servidor, agente y cliente. Es la capa mas baja de comunicacion
 * que hay en este proyecto.
 */

class Socket {
public:
    /**
     * @brief Constructor para el Socket que recibe el puerto en donde se va a conectar.
     * @param puerto es puerto por donde establecera la conexion el socket.
     */
    explicit Socket(Puerto puerto);
        
    /**
     * @brief Destructor virtual de Socket
     */
    virtual ~Socket();
    
    /**
     * @brief Intenta establecer una conexion con el huesped.
     * @param huesped string que contiene la direccione a la cual se conectara el socket.
     */
    void conectar(const std::string& huesped);
    
    /**
     * @brief Enlaza el Socket para poder escuchar conexiones entrantes
     */
    void enlazar();
    
    /**
     * @brief Escucha una conexion entrante y retorna un Socket para
     * realizar la comunicion con esta.
     * @return Instancia de otro socket conectado anfitrion.
     */
    Socket* escucharConexion();
    
    /**
     * @brief Envia el mensaje atravez del socket, confirmando si fue enviado correctamente.
     * @param mensaje Mensaje con los datos a enviar.
     * @return booleano indicando si envio correctamente el mensaje
     */
    bool enviar(const Paquete& paquete);

    /**
	 * @brief Se pone en espera a recibir una respuesta.
	 * @param mensaje Mensaje que donde se van a almacenar los datos recibidos.
	 * @return booleano indicando si se recibio correctamente el mensaje..
	 */
    bool recibir(Paquete& paquete);

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
private:
    /**
     * @brief Constructor que recibe un "file descriptor" ya inicializado.
     * @param fd "File Descriptor" del nuevo socket.
     */
    explicit Socket(int fd);
    
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

    /**
     * Constructor copia privado.
     */
    Socket(const Socket& orig) {}
    void operator=(const Socket& orig) {}
    
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

#endif	/* SOCKET_H */

