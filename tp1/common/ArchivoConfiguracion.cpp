#include "ArchivoConfiguracion.h"

#define SEPARADOR '='

std::string ArchivoConfiguracion::obtenerAtributo(std::string& name) {
	std::string ret;
	if (atributos.find(name) != atributos.end()) {
		ret = atributos[name];
	}
	return ret;
}

std::string ArchivoConfiguracion::obtenerAtributo(char* nombre) {
	std::string nm = nombre;
	return obtenerAtributo(nm);
}

ArchivoConfiguracion::iterator ArchivoConfiguracion::begin() {
	return atributos.begin();
}

ArchivoConfiguracion::iterator ArchivoConfiguracion::end() {
	return atributos.end();
}

bool ArchivoConfiguracion::formatoCorrecto(std::string& linea) {
	return (linea.find(SEPARADOR) != std::string::npos && 
	(linea.find_first_of(SEPARADOR) == linea.find_last_of(SEPARADOR)));
}

void ArchivoConfiguracion::setearAtributo(std::string& nombre, std::string& valor) {
	atributos[nombre] = valor;
}

ArchivoConfiguracion::ArchivoConfiguracion(const char* ruta): rutaArchivo(ruta), lock(ruta) {
	lock.tomarLock();
	std::fstream archivo(ruta);
	Utilitario u;
	if (!archivo) {
		archivo.open(ruta, std::fstream::out);
	} else {
		std::string aux;
		while(!archivo.eof()) {
			std::getline(archivo, aux);
			u.borrarCaracter(aux, ' ');
			if (formatoCorrecto(aux)) {
				unsigned int posSeparador = aux.find_first_of(SEPARADOR);
				std::string nombre = aux.substr(0, posSeparador);
				std::string atributo = aux.substr(posSeparador + 1);
				if (nombre.size() && atributo.size())
					atributos[nombre] = atributo;
			}
		}
	}
	archivo.close();
	lock.liberarLock();
}

ArchivoConfiguracion::~ArchivoConfiguracion() {
	lock.tomarLock();
	std::fstream archivo(rutaArchivo.c_str(), std::fstream::out);
	ArchivoConfiguracion::iterator iter;
	for (iter = begin(); iter != end(); ++iter) {
		std::string aux = iter->first + "=" + iter->second;
		archivo << aux << std::endl;
	}
	archivo.close();
	lock.liberarLock();
}
