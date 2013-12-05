

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

#include "../common/Definiciones.h"
#include "../common/SocketUDP.h"
#include "../common/Empaquetador.h"
#include "../common/GestorDeSeniales.h"

#include "SenialFinalizacion.h"

bool _seguirRecibiendo_ = true;
#define TAM_BUFFER 128

int mainReceptor(SocketUDP& receptor);

void imprimirPaquete(const Paquete& paq) {

	const char* buffer = (char*) paq.serializar();

	for (int i = 0; i < 50 ; i++) {
		std::cout << "(" <<  i << ")=" <<"\'"<< buffer[i] <<"\';  Int= " <<(int) buffer[i]<< std::endl;
		//if (i % 20 == 0)
		//std::cout << std::endl;
	}

}

void imprimir(const Empaquetador& emp) {
	printf("\r");
	fflush(stdout);

	//std::cout << "Imprimiendo Paquete" << std::endl;

	if (emp.tipoActual() == Empaquetador::MENSAJE) {
		std::cout << emp.PAQ_nombreDeUsuario() << ": ";
		std::cout << emp.PAQ_mensajeDeUsuario() << std::endl;
	}
	else if (emp.tipoActual() == Empaquetador::OK) {
		std::cout << "<< Confirmacion recibida >> : ";
		//std::cout << ";tamanio: " << emp.PAQ_mensajeDeUsuario().size() << ";";
		std::cout << emp.PAQ_mensajeDeUsuario() << std::endl;
	}
	else if (emp.tipoActual() == Empaquetador::CONVERSACIONES) {
		std::vector<std::string> conv = emp.PAQ_conversaciones();

		std::cout << "Conversaciones Disponibles";
		std::cout << "(" << conv.size() << "):" << std::endl;

		for (unsigned i = 0; i < conv.size() ; i++) {
			std::cout << i+1 << ": " << conv[i] << std::endl;
		}
	}
	else if (emp.tipoActual() == Empaquetador::USUARIOS_CONVERSACION) {

		const std::vector<std::string> &conv = emp.PAQ_usuariosEnConversacion();

		std::cout << "Conversacion \"" << conv[0] << "\":" << std::endl;
		for (unsigned i = 1 ; i < conv.size() ; i++)
			std::cout << "\t - " << conv[i] << std::endl;

	}
	else if (emp.tipoActual() == Empaquetador::USUARIOS_EN_LINEA) {
		const std::vector<std::string> &usuarios = emp.PAQ_usuariosEnLinea();

		std::cout << "Usuarios en linea: "<< std::endl;
		for (unsigned i = 1 ; i < usuarios.size() ; i++)
			std::cout << "\t- " << usuarios[i] << std::endl;

	}
	else if (emp.tipoActual() == Empaquetador::FIN_SESION) {
		std::cout << emp.PAQ_nombreDeUsuario() << std::endl;
	}
	else if (emp.tipoActual() == Empaquetador::SERVIDOR_CERRADO) {
		std::cout << "<<< El servidor se ha apagado >>> " << std::endl;
	}
	else if (emp.tipoActual() == Empaquetador::ERROR) {
		std::cout << emp.PAQ_mensajeDeError() << std::endl;
	}
	else {
		std::cout << "Error: Mensaje no reconocible" << std::endl;
		imprimirPaquete(emp.paquete());
	}

	std::cout << std::endl << ">> ";
	std::cout.flush();
}

void imprimirOpciones() {
	std::cout << "Opciones " << std::endl;
	std::cout << ".1 : Elegir conversaciones." << std::endl;
	std::cout << ".2 : Unirse a una conversacion." << std::endl;
	std::cout << ".3 : Crear conversaciones." << std::endl;
	std::cout << ".4 : Ver usuarios en conversacion (inngrese nombre vacio para consultar en conversacion actual)." << std::endl;
	std::cout << ".5 : Ver todos los usuarios en linea." << std::endl;
	std::cout << std::endl;
	std::cout << ".0 : Finalizar sesion." << std::endl;
}

int main() {

	std::string usuario;
	Empaquetador emp;

	DirSocket dirServidor;
	SocketUDP _sock;
	_sock.enlazar(0);
	DirSocket dirRealServ;

	char buffer[TAM_BUFFER];
	{
		std::string nombreServidor = "localhost";
		dirServidor = _sock.direccionServidor(PUERTO_SERVIDOR, nombreServidor);
		bool _conectado = false;
		Paquete paqRecibido;
		int intentos = 3;
		bool intentarConectar = true;

		while (_conectado == false && intentos > 0 && intentarConectar) {

			std::cout << "Ingrese Nombre de Usuario: ";
			std::cin.getline(buffer, 128);
			usuario = buffer;
			//getline(std::cin, mensaje);

			if (usuario == ".salir") {
				intentarConectar = false;
			}
			else {

				emp.iniciarSesion(usuario);

				if (_sock.enviar(emp.paquete(), dirServidor) == true)
					std::cout << "Solicitud de conexion enviada." << std::endl;

				emp.limpiar();

				if (_sock.recibir(paqRecibido, dirRealServ) == true)
					emp.asociar(paqRecibido);

				imprimir(emp);

				if (emp.PAQ_confirmacionRecibida()) {
					_conectado = true;
				}
				else if (emp.PAQ_errorRecibido()) {
					std::cout << "(Ingrese otro nombre de usuario o \".salir\" para finalizar.)" << std::endl;
				}
				else {
					intentos--;
					std::cout << "intentando conectarse nuevamente en 2 seg..." << std::endl;
					sleep(2);
				}
			}

		}

		if (intentarConectar == false)
			return 0;


		if (_conectado == false) {
			std::cout << "No se pudo conectar con servidor" << std::endl;
			return -1;
		}

	}

	int pid = fork();

	if (pid == 0)
		return mainReceptor(_sock);


	std::string mensaje;

	//Empaquetador::TipoPaquete paqAnterior = Empaquetador::DESCONOCIDO;

	std::cout << "Ingrese \".op\" para ver las opciones." << std::endl;

	bool enviar = false;
	while (_seguirRecibiendo_) {

		std::cout << std::endl << ">> ";
		std::cin.getline(buffer, TAM_BUFFER);
		mensaje = buffer;

		if (mensaje.size() >= 2 && mensaje[0] == '.') {
			int tamanio = mensaje.size();

			if (tamanio == 2) {

				if ( mensaje[1] == '1' ) {
					emp.verConversaciones(usuario);
					enviar = true;
				}
				else if ( mensaje[1] == '2' ) {
					std::cout << "ingrese nombre de la conversacion a unirse: ";
					std::cin.getline(buffer, TAM_BUFFER);
					mensaje = buffer;
					if (mensaje.size() > 0) {
						//std::cout << "por enviar: " << mensaje << std::endl;
						emp.unirseConversacion(usuario, mensaje);
						enviar = true;
					}
				}
				else if (mensaje[1] == '3') {
					std::cout << "ingrese nombre de nueva conversacion: ";
					std::cin.getline(buffer, TAM_BUFFER);
					mensaje = buffer;
					if (mensaje.size() > 0) {
						//std::cout << "por enviar: " << mensaje << std::endl;
						emp.crearConversacion(usuario, mensaje);
						enviar = true;
					}
				}
				else if (mensaje[1] == '4') {
					std::cout << "ingrese nombre de conversacion a consultar: ";
					std::cin.getline(buffer, TAM_BUFFER);
					mensaje = buffer;

					emp.usuariosEnConversacion(usuario, mensaje);
					enviar = true;

				}
				else if (mensaje[1] == '5') {
					emp.solicitarUsuariosEnLinea(usuario);
					enviar = true;

				}
				else if (mensaje[1] == '0') {
					enviar = true;
					emp.finalizarSesion(usuario);
					_seguirRecibiendo_ = false;
				}
			}
			else if (mensaje.size() == 3 && mensaje[0] == '.' && mensaje[1] == 'o' && mensaje[2] == 'p') {
				imprimirOpciones();
			}
			else {
				std::cout << "<< Opcion no reconocida >>." << std::endl;
			}

		}
		else if (mensaje.size() > 0) {
			emp.agregarMensaje(usuario, mensaje);
			enviar = true;
		}

		if (enviar == true && _sock.enviar(emp.paquete(), dirRealServ) == false) {
			std::cout << "Error: mensaje no se pudo enviar" << std::endl;
		}
		enviar = false;
	}

	Paquete paqFinalizacion;

	GestorDeSeniales::instancia().enviarSenialAProceso(pid, SIGNUM_FINALIZACION);

	int intentosSalida = 2;
	int estadoSalida;
	do {
		std::cout << "Esperando finalizacion..." << std::endl;
		waitpid(pid, &estadoSalida, 0);

		intentosSalida--;
		if (WIFEXITED(estadoSalida) == false && intentosSalida == 0)
			GestorDeSeniales::instancia().enviarSenialAProceso(pid, SIGNUM_FINALIZACION);
	} while (WIFEXITED(estadoSalida) == false && intentosSalida > 0);

	return 0;
}

int mainReceptor(SocketUDP &receptor) {

	SenialFinalizacion senial;
	GestorDeSeniales::instancia().agregarSenial(senial);

	Empaquetador emp;
	Paquete paq;
	DirSocket aux;

	bool servidorAbierto = true;

	while (_seguirRecibiendo_) {
		if (servidorAbierto && receptor.recibir(paq, aux) == true) {
			emp.asociar(paq);

			if (emp.PAQ_sevidorCerrado()) {
				servidorAbierto = false;
			}

			imprimir(emp);
		}
	}

	if (servidorAbierto) {
		if (receptor.recibir(paq, aux) == true) {
			emp.asociar(paq);
			imprimir(emp);
		}
		else {
			std::cout << "Error: no se recibio confirmacion de finalizacion." << std::endl;
		}
	}
	return 0;
}

