#ifndef _ARCHIVOCONFIGURACION_H
#define _ARCHIVOCONFIGURACION_H

#include <fstream>
#include <string>
#include <map>
#include "Utilitario.h"
#include "LockFile.h"
#define RUTA "archivo.configuracion"

/** @class ArchivoConfiguracion

* Es una clase de archivo que contiene atributos levantados de un archivo
* de texto. El archivo a levantar se encuentra encriptado.
* Nota: esta clase no es thread-safe.
*/

class ArchivoConfiguracion {
private:
	std::string rutaArchivo;
	std::map<std::string, std::string> atributos;
	bool formatoCorrecto(std::string& linea);
	LockFile lock;
public:
	typedef std::map<std::string, std::string>::iterator iterator;
	
	/** Devuelve el atributo asociado */
	std::string obtenerAtributo(std::string& name);
	
	/** @see obtenerAtributo */
	std::string obtenerAtributo(char* nombre);
	
	/** Setea el atributo "nom" con "valor" */
	void setearAtributo(std::string& nom, std::string& valor);
	iterator begin();
	iterator end();
	
	/** Si el archivo no existe, no levanta ningun tipo de excepcion */
	explicit ArchivoConfiguracion(const char* ruta = RUTA);
	
	/** En el destructor es que se persisten los cambios del archivo */
	~ArchivoConfiguracion();

};

#endif
