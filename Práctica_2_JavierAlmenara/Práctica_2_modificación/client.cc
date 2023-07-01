/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 2: Representación de números grandes en notación posicional
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 06/02/2023
 * @file: client.cc
 *    Archivo cliente.
 */

#include "bigint.h"
#include "calculator.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include "functions.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
  BigInt<2, char> n {12}, m {2};
  BigInt<2, bool> a {12}, b {2};
  std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
  n = n * m;
  std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;
  startTime = std::chrono::high_resolution_clock::now();
  a = a * b;
  endTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsedTime_2 = endTime - startTime;
  std::cout << "El tamaño que ocupa el objeto en memoria dinámica, del objeto con char es : " << sizeof(n) << std::endl;
  std::cout << "Tiempo: " << elapsedTime.count() << " ms.\n";
  std::cout << "El tamaño que ocupa el objeto en memoria dinámica, del objeto con bool es : " << sizeof(a) << std::endl;
  std::cout << "Tiempo: " << elapsedTime_2.count() << " ms.\n";
}