/*
 * Resolvedor.cpp
 *
 *  Created on: 23/11/2013
 *      Author: migue
 */

#include "Resolvedor.h"
#include "../common/Empaquetador.h"


Resolvedor* Resolvedor::_instancia = NULL;

Resolvedor::Resolvedor() :_emisor() , _semResolvedor(SEM_RESOLVEDOR, 1), _seguirEnviando(true) {

	_emisor.enlazar(0);
	_ultimoIDLibre = 1;
	_usarSemaforo = true;
}

void Resolvedor::usarSemaforos(bool usar) {
	_usarSemaforo = usar;
}

void Resolvedor::wait() {
	if (_usarSemaforo == true)
		_semResolvedor.wait();
}

void Resolvedor::signal() {
	if (_usarSemaforo == true)
		_semResolvedor.signal();
}

Resolvedor& Resolvedor::instanacia() {
	if (_instancia == NULL)
		_instancia = new Resolvedor();
	return *_instancia;
}

bool Resolvedor::instanciado() {
	return (_instancia != NULL);
}

Resolvedor::~Resolvedor() {

}

void Resolvedor::liberar() {
	if (_instancia != NULL) {
		delete _instancia;
		_instancia = NULL;
	}
}

void Resolvedor::dejarDeResponder() {
	_seguirEnviando = false;
}

int Resolvedor::comenzar() {
	Paquete solicitud, respuesta;

	Destinatarios destinos;
	while (_seguirEnviando) {

		solicitud = _colaPaquetes.sacar();

		respuesta = resolver(solicitud, destinos);

		enviar(respuesta, destinos);
	}

	return 0;
}


const Paquete Resolvedor::resolver(const Paquete& origen, Destinatarios& destinos) {
	wait();

	const Empaquetador emp(origen);
	Empaquetador respuesta;
	destinos.clear();

	if (emp.tipoActual() == Empaquetador::MENSAJE) {
		respuesta.asociar(this->reenviarMensaje(origen, destinos));
	}
	else if (emp.tipoActual() == Empaquetador::INICIO_SESION) {
		respuesta.asociar(this->agregarUsuario(origen));
	}
	else if (emp.tipoActual() == Empaquetador::FIN_SESION) {
		respuesta.asociar(this->finalizarSesion(emp, destinos));
	}
	else if (emp.tipoActual() == Empaquetador::OK) {
		respuesta.limpiar();
	}
	else if (emp.tipoActual() == Empaquetador::CREAR_CONVERSACION) {
		respuesta.asociar(this->crearConversacion(emp, destinos));
	}
	else if (emp.tipoActual() == Empaquetador::UNIRSE_CONVERSACION) {
		respuesta.asociar(this->unirseConversacion(emp, destinos));
	}
	else  {
		respuesta.asociar(this->paqueteNoValido(emp, destinos));
	}


	signal();
	return respuesta.paquete();
}

const Paquete Resolvedor::finalizarSesion(const Empaquetador& empaquetador, Destinatarios& destinos) {
	Empaquetador res;

	IdUsuario idUsr = empaquetador.PAQ_nombreDeUsuario();
	itUsuarios it = _usuarios.find(idUsr);

	if (it != _usuarios.end()) {

		if (it->second.id_conv != 0) {
			IdConversacion idConv = it->second.id_conv;
			this->eliminarUsuarioDeConversacion(idConv, idUsr);
		}

		_usrAEliminar.push_back(idUsr);

		res.confirmarRespuesta();
		destinos.push_back(idUsr);
	}

	return res.paquete();
}

void Resolvedor::eliminarUsuarioDeConversacion(const IdConversacion& idConv, const IdUsuario& idUsr) {
	Destinatarios& dest = _usrXConv[idConv];
	bool encontrado = false;
	unsigned indice = 0;

	while(indice < dest.size() && encontrado == false) {

		if (*(dest.begin() + indice) == idUsr ) {
			encontrado = true;
			dest.erase(dest.begin() + indice);
		}

		indice++;
	}

	if (dest.size() == 0) {
		_usrXConv.erase(idConv);

		itConversaciones itConv = _conversaciones.begin(), itAEliminar;
		encontrado = false;

		while (itConv != _conversaciones.end() && encontrado == false) {
			if (itConv->second == idConv) {
				encontrado = true;
				itAEliminar = itConv;
			}
			itConv++;
		}

		if (encontrado) {
			_conversaciones.erase(itAEliminar);
		}
	}
}

const Paquete Resolvedor::paqueteNoValido(const Empaquetador& emp, Destinatarios& destinos) {
	Empaquetador res;

	res.agregarMensajeError("Paquete no valido para procesar");

	return res.paquete();
}


const Paquete Resolvedor::reenviarMensaje(const Empaquetador& empaquetador, Destinatarios& destinos) {
	Empaquetador res;
	IdUsuario idUsr = empaquetador.PAQ_nombreDeUsuario();
	itUsuarios itUsr = _usuarios.find(idUsr);

	if (itUsr != _usuarios.end()) {

		IdConversacion idConv = itUsr->second.id_conv;


		if (_usrXConv.find(idConv) != _usrXConv.end()) {
			res.asociar(empaquetador.paquete());
			this->agregarDestinos(idConv, destinos);
		}
		else {
			res.agregarMensajeError("No se encuentra en ninguna conversacion");
			destinos.push_back(itUsr->first);
		}
	}

	return res.paquete();
}

const Paquete Resolvedor::agregarUsuario(const Paquete& paquete) {
	Empaquetador emp(paquete);

	std::string nomUsr = emp.PAQ_nombreDeUsuario();

	itUsuarios it = _usuarios.find(nomUsr);
	if (it == _usuarios.end()) {

		InfoUsuario infoUsr;
		infoUsr.id_conv = 0;
		infoUsr.pid = 0;
		//infoUsr._dirSock;

		_usuarios.insert(parUsuarios(nomUsr, infoUsr));

		emp.limpiar();
		emp.confirmarRespuesta();
	}
	else {
		emp.limpiar();
		emp.agregarMensajeError("Nombre de Usuario ya existe");
	}


	return emp.paquete();
}

const Paquete Resolvedor::crearConversacion(const Empaquetador& empaquetador, Destinatarios& destinos){
	Empaquetador res;

	std::string nombreConversacion(empaquetador.PAQ_nombreConversacion());

	if (nombreConversacion.size() == 0) {
		res.agregarMensajeError(std::string("No hay nombre para crear la nueva conversacion"));
		return res.paquete();
	}

	itConversaciones it = _conversaciones.find(nombreConversacion);

	if (it == _conversaciones.end()) {
		//it->first = nombreConversacion;
		//it->second = _ultimoIDLibre;
		_conversaciones.insert(parConversaciones(nombreConversacion, _ultimoIDLibre));

		_ultimoIDLibre++;
		res.confirmarRespuesta();

		Destinatarios destVacio;

		_usrXConv[it->second] = destVacio;

		Empaquetador empUnion;
		empUnion.unirseConversacion(empaquetador.PAQ_nombreDeUsuario(), empaquetador.PAQ_nombreConversacion());

		res.asociar(this->unirseConversacion(empUnion,destinos));
	}
	else {
		res.agregarMensajeError(std::string("Conversacion ya existe"));
	}


	return res.paquete();
}

const Paquete Resolvedor::unirseConversacion(const Empaquetador& empaquetador, Destinatarios& destinos){
	Empaquetador res;

	std::string nombreUsuario = empaquetador.PAQ_nombreDeUsuario();
	std::string nombreConv = empaquetador.PAQ_nombreConversacion();

	itUsuarios itUsr = _usuarios.find(nombreUsuario);
	itConversaciones itConv = _conversaciones.find(nombreConv);


	if (itUsr != _usuarios.end() && itConv != _conversaciones.end()) {

		// agrego el id de conversacion al usuario.
		itUsr->second.id_conv = itConv->second;

		// agrego el usuario a la lista de integrantes de una conversacion
		_usrXConv[itConv->second].push_back(nombreUsuario);

		res.agregarMensaje(nombreUsuario, ":::Se ha unido a la conversacion:::");
		this->agregarDestinos(itConv->second, destinos);
	}
	else {
		res.agregarMensajeError("Usuario No existe");
	}

	return res.paquete();
}


void Resolvedor::agregarDestinos(IdConversacion id, Destinatarios& destinos) {
	itConvUsuarios it = _usrXConv.find(id);

	if (it != _usrXConv.end()) {
		destinos = it->second;
	}
}


void Resolvedor::enviar(const Paquete& paqueteRespuesta, const Destinatarios& destinos) {

	wait();

	Destinatarios::const_iterator it = destinos.begin();

	while (it != destinos.end()) {
		this->enviarPaquete(*it , paqueteRespuesta);
	}


	eliminarUsuariosFinalizados();

	signal();
}

void Resolvedor::enviarPaquete(IdUsuario id, const Paquete& paq)  {
	itUsuarios it = _usuarios.find(id);

	if (it != _usuarios.end()) {
		_emisor.enviar(paq, it->second._dirSock);
	}
}

const Paquete Resolvedor::agregarNuevoUsuario(const NuevoUsuario& info) {
	_semResolvedor.wait();

	std::string nombreUsr = info.nombre;

	Empaquetador emp;
	emp.iniciarSesion(nombreUsr);
	Destinatarios dest;

	Paquete res = this->resolver(emp.paquete(), dest);

	const Empaquetador emp2(res);

	if (emp2.PAQ_confirmacionRecibida()) {
		itUsuarios it = _usuarios.find(nombreUsr);
		it->second._dirSock = info._dirSck;
		it->second.id_conv = 0;
		it->second.pid = info.pid_receptor;

		// TODO verificar si ya con esto quedo modificado el mapa
	}

	_semResolvedor.signal();

	return emp2.paquete();
}

void Resolvedor::eliminarUsuariosFinalizados() {

	for ( unsigned i = 0; i < _usrAEliminar.size(); i++) {
		IdUsuario& idUsr = _usrAEliminar.at(i);
		_usuarios.erase(idUsr);
	}

	_usrAEliminar.clear();
}
