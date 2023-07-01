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
  BigInt<10> numero_introducido;
  std::cout << "Introduzca un número BigInt: ";
  std::cin >> numero_introducido;
  /// Caso 0
  int a = 0;
  std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
  std::cout << numero_introducido << " ^ " << a << " : " << power<10>(numero_introducido, a) << std::endl;
  std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;
  std::cout << "Tiempo: " << elapsedTime.count() << " ms.\n";
  startTime = std::chrono::high_resolution_clock::now();
  std::cout << numero_introducido << " ^ " << ++a << " : " << power<10>(numero_introducido, a) << std::endl;
  endTime = std::chrono::high_resolution_clock::now();
  elapsedTime = endTime - startTime;
  std::cout << "Tiempo: " << elapsedTime.count() << " ms.\n";
  for (int i = 10; i <= 1000; i += 10) {
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    std::cout << numero_introducido << " ^ " << i << " : " << power<10>(numero_introducido, i) << std::endl;
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;
    std::cout << "Tiempo: " << elapsedTime.count() << " ms.\n";
  }
  return 0;
}