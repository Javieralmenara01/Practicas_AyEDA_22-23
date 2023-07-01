/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 3: Calculadora universal para números enteros grandes
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 01/03/2023
 * @file: functions.cc
 *    Definición de funciones.
 */

#include "functions.h"

/**
 * Función Usage
 * @brief Nos permite controlar las opciones introducidas, así como si el fichero de lectura es válido.
 */
void Usage(int argc, char** argv) {
  if (argc == 3) {
    std::ifstream file {argv[1]};
    if (!file.good()) {
      throw std::invalid_argument("Archivo introducido inválido!\n");
    }
  } else {
    throw std::invalid_argument("Número de argumentos inválido!\n");
  }
}

/**
 * Función Usage
 * @brief Nos permite explicar el funcionamiento del programa.
 */
void Help() {
  std::cerr << "\n###### Modo de funcionamiento del programa #####" << std::endl;
  std::cerr << "Pruebe: ./client file.in file.out" << std::endl;
}

/**
 * Función Get Base
 * @brief Nos permite obtener la base dada en un fichero de entrada.
 */
int GetBase(const std::string& s) {
  std::stringstream stream_line{s};
  std::string aux;
  stream_line >> aux >> aux >> aux;
  return stoi(aux);
}

/**
 * Función Remove Comma
 * @brief Nos permite eliminar la coma final si la hubiere de una cadena.
 */
int RemoveComma(const std::string& s) {
  std::string aux = s;
  if (s[s.length() - 1] == ',') {
    aux.pop_back();
  }
  return stoi(aux);
}

/**
 * Función Return Value
 * @brief Nos permite obtener la base de un objeto aputando por un puntero, de la clase BigInt<Base>.
 */
std::string ReturnValue(const char* s) {
  bool condition = false;
  std::string aux, s_final;
  for (size_t i = 0; i < strlen(s); i++) {
    aux.push_back(s[i]);
    if (aux == "6BigIntILm") {
      condition = true;
    } else if (s[i] == 'E' && condition) {
      break;
    } else if (condition) {
      s_final.push_back(s[i]);
    }
  }
  return s_final;
}