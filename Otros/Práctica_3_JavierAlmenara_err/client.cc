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
#include "bigintexcepcion.h"

int main(int argc, char** argv) {
  Number* num = new BigInt<2> (2);
  std::cout << *num << std::endl;
  return 0;
}