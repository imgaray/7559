#include "Paquete.h"
#include <string.h>


Paquete::Paquete() {
	_tipo = 0;
	_ultimaPosicion = TAM_CABECERA;
	_tamanioReal = TAM_CABECERA;
}

Paquete::Paquete(const void* spaquete) {
	this->deserializar(spaquete);
}

Paquete::Paquete(const Paquete& orig) {
	*this = orig;
}

const Paquete& Paquete::operator =(const Paquete& orig) {
	_tipo = orig._tipo;
	_tamanioReal = orig._tamanioReal;
	_msj = orig._msj;
	_ultimaPosicion = orig._ultimaPosicion;

	copiar((char*)_buffer,(char*)orig._buffer, TAM_MAX_PAQ);

	return *this;
}

Paquete::~Paquete() {

}

int Paquete::tamanio() const {
	return TAM_MAX_PAQ;
}

void Paquete::definirTipo(int tipo) {
	_tipo = tipo;
	_buffer[2] = _tipo;
}

int Paquete::tipo() const {
	return _tipo;
}

void Paquete::leerCabecera() {
	unsigned char* cdatos = _buffer;

	_tamanioReal = cdatos[0];
	_tamanioReal = _tamanioReal << 8;
	_tamanioReal += cdatos[1];

	_tipo = cdatos[2];
}

void Paquete::actualizarCabecera() {
	_buffer[0] = (_tamanioReal >> 8) & 0xff;
	_buffer[1] = _tamanioReal & 0xff;

	_buffer[2] = _tipo;
}

void Paquete::deserializar(const void* datos) {
	copiar((char*)_buffer, (char*)datos,TAM_MAX_PAQ);
	leerCabecera();
	_ultimaPosicion = _tamanioReal;
}

void Paquete::limpiar() {
	_tamanioReal = TAM_CABECERA;
	_ultimaPosicion = TAM_CABECERA;
	_msj.clear();
	_tipo = 0;
}

const std::string Paquete::mensaje() const {
	std::string res = (char*)(_buffer + TAM_CABECERA);


	if ((_tamanioReal  - TAM_CABECERA) > 0) {
		res.resize(_tamanioReal - TAM_CABECERA);
	}
	else {
		res.clear();
	}

	return res;
}

void Paquete::agregarDatos(const void* datos, int tamanio) {
	if ( ( tamanio + _ultimaPosicion ) < TAM_MAX_PAQ ) {
		copiar((char*)(_buffer + _ultimaPosicion),(char*) datos,tamanio);
		_tamanioReal += tamanio;
		_ultimaPosicion += tamanio;

		actualizarCabecera();
	}
}

const void* Paquete::serializar() const {
	return (void*) _buffer;
}

char* Paquete::atributo(int indice) const {
	char* res = NULL;

	int posBuffer = TAM_CABECERA,  i = 0;;
	unsigned tamLocal;
	bool encontrado = false;

	while (posBuffer < TAM_MAX_PAQ && i <= indice && encontrado == false) {
		tamLocal = _buffer[posBuffer];
		if ( i == indice && ( posBuffer + tamLocal < TAM_MAX_PAQ ) ) {
			res = new char[tamLocal + 1];
			copiar( res,(char*)( _buffer + posBuffer + 1), tamLocal );
			res[tamLocal] = '\0';
			encontrado = true;
		}
		else {
			i++;
			posBuffer += tamLocal + 1;
		}
	}

	return res;
}

void Paquete::agregarAtributo(void* datos, unsigned tamanio) {
	if (( _ultimaPosicion + tamanio ) < TAM_MAX_PAQ ) {

		_buffer[_ultimaPosicion] = tamanio;
		_ultimaPosicion++;

		copiar((char*)(_buffer + _ultimaPosicion), (char*) datos, tamanio);
		_tamanioReal += tamanio;
		_ultimaPosicion += tamanio;
	}

	actualizarCabecera();
}

void Paquete::copiar(char* destino, const char* origen, int cantidad) const {
	for (int i = 0; i < cantidad ; i++)
		destino[i] = origen[i];
}
