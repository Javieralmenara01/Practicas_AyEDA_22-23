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
 * @file: client.cc
 *    Programa cliente
 */

#include "bigint.h"
#include "racional.h"
#include "bigintexception.h"
#include "calculator.h"
#include "functions.h"
#include <typeinfo>

/**
 * Function Main
 * @brief Función principal del programa cliente.
 * @param argc : Nos permite obtener el número de argumentos pasados por línea de comandos en la ejecución.
 * @param argv : Nos permite obtener los argumentos pasados por línea de comandos en la ejecución.
 */
int main(int argc, char** argv) {
  Number* num_a = new Racional(2, 1);
  Number* num_b = new Racional(3, 1);
  Number* result = num_a->multiply(num_b);
  std::cout << *result << std::endl;
  return 0;
}