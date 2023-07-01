/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 1: Representación de números grandes en notación posicional
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 06/02/2023
 * @file: functions.cc
 *    Definición de funciones.
 */

#include "functions.h"

/**
 * Función Usage
 * @brief Nos permite controlar las opciones introducidas, así como el fichero de lectura es válido
 */
void Usage(int argc, char** argv) {
  if (argc == 3) {
    std::ifstream file {argv[1]};
    if (!file.good()) {
      throw std::invalid_argument("Archivo introducido inválido!");
    }
  } else {
    throw std::invalid_argument("Número de argumentos inválido!");
  }
}

