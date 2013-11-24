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
 * Constantes del Servidor
 */

const Puerto PUERTO_SERVIDOR = 9090;

#define CANT_PAQ_COLA 100


/**
 * Nombres de Semaforos Posix
 */


#define SEM_INTERCAMBIO_RYR 			"sem_int_ryr"
#define SEM_MEM_COMP_INTERCAMBIO_RYR	"sem_mem_comp_ryr"


#define SEM_COLA_PAQ_SACAR			"sem_cola_paq_poner"
#define SEM_COLA_PAQ_PONER			"sem_cola_paq_poner"
#define SEM_MEM_COMP_COLA_PAQ		"sem_mem_comp_cola_paq"
#define MEM_COMP_COLA_PAQ			"/tmp/cola_paquetes"

/**
 * Estructuras usadas en el resolvedor.
 */

typedef std::pair<int, DirSocket> InfoUsuario;

typedef int IdConversacion;

typedef std::vector<IdConversacion> Destinatarios;
typedef std::map<std::string, IdConversacion> Conversaciones;
typedef std::map<IdConversacion, Destinatarios > ConvUsuarios;
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
