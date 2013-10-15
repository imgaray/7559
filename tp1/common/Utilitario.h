#ifndef UTILITARIO_H_
#define UTILITARIO_H_
#include <string>
#include <vector>
#include <sstream>

/**
 * @class Utilitario
 *      Esta clase es usada para realizar operaciones auxiliares como separar un
 *      string en varios, borrar caracteres de un string, convertir un string en entero
 *      y al reves.
 */

class Utilitario {
public:
        /**
         * @brief Constructor sin argumentos.
         */
        Utilitario();
        virtual ~Utilitario();

        /**
         * @brief Metodo utilizado para separa un string en partes, separadas por un caracter.
         * @param datos string a separar.
         * @param separador caracter utilizado como delimitador de las partes en el string.
         * @param indice numero que representa que parte se va a serpara del string.
         * @return string que contiene el segmento extraido del string principal.
         */
        std::string separar(const std::string& datos,
                        const char separador, const size_t indice);

        /**
         * @brief Transforma un numero en string.
         * @param numero valor numerico a transforma
         * @return string que contiene el numeor tranformado.
         */
        std::string convertirAString(const int& numero) const;

        /**
         * @brief Transforma un string en su valor numerico.
         * @param numero string que contiene los caractes de digitos.
         * @return entero que contiene el valor numerico del string.
         */
        int convertirAEntero(const std::string& numero) const;

        /**
         * @brief Borra un caracter de todo un string.
         * @param palabra string al cual se eliminaran los caracteres.
         * @param caracter char a borrar del string.
         */
        void borrarCaracter(std::string& palabra, const char caracter);
private:
        std::vector <size_t> _posiciones;
        std::string s_anterior;
        char sep_anterior;
};

#endif /* UTILITARIO_H_ */
