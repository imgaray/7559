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
#include <signal.h>
/**
 * Constantes del Servidor
 */

const Puerto PUERTO_SERVIDOR = 9091;

#define CANT_PAQ_COLA 100


/**
 * Nombres de Semaforos Posix
 */

#define SEM_RESOLVEDOR					"/tmp/sem_resolvedor" // semaforo para una exclusion mutua del las estructuras del resolvedor
#define SEM_INTERCAMBIO_RYR 			"/tmp/sem_int_ryr"	// semaforo para sincronizar recibidor con y receptor
#define SEM_RECIBIDOR					"/tmp/sem_recibidor"


#define SEM_COLA_PAQ_SACAR			"/tmp/sem_cola_paq_sacar"
#define SEM_COLA_PAQ_PONER			"/tmp/sem_cola_paq_poner"
#define SEM_MEM_COMP_COLA_PAQ		"/tmp/sem_mem_comp_cola_paq"


/**
 * Rutas de archivos para memoria compartida
 */

#define MEM_COMP_COLA_PAQ			"/tmp/cola_paquetes"
#define MC_INTCMB_RECIBIDOR 		"/tmp/recibidor"
#define PROJ_ID_RESOLVEDOR			'a'
#define PROJ_ID_RECIBIDOR			'b'

/**
 * NUMEROS DE SEÑALES
 */

#define SIGNUM_INTERCAMBIO_RESOLVEDOR 			SIGUSR1

#define SIGNUM_FINALIZACION						SIGINT

#define SIGNUM_ESPERA_CONFIRMACION				SIGSTOP
#define SIGNUM_CONFIRMACION						SIGCONT
#define SIGNUM_CONFIRMACION_NEGATIVA			SIGINT

/**
 * Estructuras usadas en el resolvedor.
 */

// SI idConversacion == 0 => conversacion inexistente
typedef int IdConversacion;
typedef std::string IdUsuario;


typedef struct {
	int pid;
	IdConversacion id_conv;
	DirSocket _dirSock;
} InfoUsuario;



typedef std::vector<IdUsuario> Destinatarios;

typedef std::map<std::string, IdConversacion> Conversaciones;
typedef std::pair<std::string, IdConversacion> parConversaciones;

typedef std::map<IdConversacion, Destinatarios > ConvUsuarios;

typedef std::pair<IdUsuario,  InfoUsuario> parUsuarios;
typedef std::map<IdUsuario,  InfoUsuario> Usuarios;
typedef Destinatarios UsuariosAEliminar;

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
