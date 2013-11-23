/*
 * Definiciones.h
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

#include "SocketUDP.h"
#include <map>
#include <string>
#include <vector>

/**
 * Nombres de Semaforos Posix
 */


#define SEM_INTERCAMBIO_RYR 			"sem_int_ryr"
#define SEM_MEM_COMP_INTERCAMBIO_RYR	"sem_mem_comp_ryr"
#define SEM_COLA_PAQ_RECIBIDOS			"sem_cola_paq"


/**
 * Estructuras usadas en el resolvedor.
 */

typedef std::pair<int, DirSocket> InfoUsuario;


typedef std::vector<int> Destinatarios;
typedef std::map<int, std::string> Conversaciones;
typedef std::map<std::string, Destinatarios > ConvUsuarios;
typedef std::map<std::string,  InfoUsuario> Usuarios;


typedef Usuarios::iterator itUsuarios;
typedef ConvUsuarios::iterator itConvUsuarios;
typedef Conversaciones::iterator itConversaciones;


/**
 * Estructuras de intercambio
 */

#define TAM_MAX_NOMBREUSR 32

typedef struct {
	int pid_receptor;
	char  nombre[TAM_MAX_NOMBREUSR];
	DirSocket _dirSck;
} NuevoUsuario;



#endif /* DEFINICIONES_H_ */
