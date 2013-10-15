#include "Utilitario.h"
#define STR_NULA ""

Utilitario::Utilitario() {
        s_anterior.clear();
        _posiciones.clear();
        sep_anterior = 0;
}

Utilitario::~Utilitario() {
}


std::string Utilitario::separar(const std::string& datos,
                const char separador, const size_t indice) {
        size_t pos_sep = -1;
        size_t cant_sep = 0;

        if (s_anterior != datos || sep_anterior != separador) {
                _posiciones.clear();
                s_anterior.clear();
                s_anterior = datos;
                sep_anterior = separador;
                bool hayMasSeparadores = true;
                while (hayMasSeparadores) {
                        pos_sep = datos.find(separador, pos_sep + 1);

                        if (pos_sep != std::string::npos) {
                                _posiciones.push_back(pos_sep);
                                cant_sep++;
                        }
                        else{
                                hayMasSeparadores = false;
                        }
                }
        }

        // si no tiene separadores retorna le dato entero para "indice" = 0
        if ((_posiciones.size() == 0) && (indice == 0)) {
                return datos;
        }

        if (_posiciones.size() > 0 && _posiciones.size() >= indice) {
                std::string arg;
                if (indice == 0) {
                        arg = datos;
                        arg.resize(_posiciones[0]);
                }
                else {
                        arg = &datos.c_str()[_posiciones[indice - 1] + 1];
                }

                // caso para el ultimo argumento
                if (indice == _posiciones.size())
                        arg.resize(datos.size() - _posiciones[indice - 1] - 1);
                else if (indice > 0)
                        arg.resize(_posiciones[indice] - _posiciones[indice - 1] - 1);

                return arg;
        }
        else {
                // retorno string nulo si indice > cantArgumentos
                return STR_NULA;
        }
}


std::string Utilitario::convertirAString(const int& numero) const {
        std::stringstream ss;
        std::string res;


        if (numero == 0)
                res = "0";
        else {
                ss << numero;
                ss >> res;
        }

        return res;
}

int Utilitario::convertirAEntero(const std::string& numero) const {
        std::stringstream ss;
        int res;

        ss << numero;
        ss >> res;

        return res;
}


void Utilitario::borrarCaracter(std::string& palabra, const char caracter) {
        std::string aux;
        std::string parte = separar(palabra, caracter, 0);

        int i = 1;
        int cantBorrada = 0;
        do {
                cantBorrada++;
                aux += parte;
                parte = separar(palabra, caracter, i);
                i++;
        } while ((aux.size() + cantBorrada)< palabra.size());

        palabra = aux;
}
