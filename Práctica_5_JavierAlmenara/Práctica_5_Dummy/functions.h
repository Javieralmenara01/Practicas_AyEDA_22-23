/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 5: Ordenación
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 06/04/2023
 * @file: functions.h
 *    Declaración de las funciones usadas en el programa
 */

#pragma once

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"
#define BLCK "\033[1m"

void StartProgram();
unsigned ObtainAlgorithm();
unsigned ObtainSize();
double ObtainAlpha();
bool ObtainConditionRandom();
bool RepeatProgram();

/// Estas funciones han sido declaradas en el fichero.h debido al uso de plantillas

/**
 * Función PrintVector
 * @brief Permite imprimir un vector
 * @param vect : vector a imprimir
 * @param ini : inicio del vector a imprimir
 * @param fin : final del vector a imprimir
 */
template <class Key>
void PrintVector(const std::vector<Key>& vect, const unsigned ini = 1, const unsigned fin = 0) {
  unsigned init_pos = ini, final_pos = fin;
  if (ini == 1 && fin == 0) {
    init_pos = 0;
    final_pos = vect.size();
  }
  std::cout << "{";
  for (int i = init_pos; i < final_pos; i++) {
    auto it = vect[i];
    if ((int)it != 0) {
      std::cout << " " << it << ",";
    }
  }
  std::cout << "\b";
  if (init_pos != final_pos) {
    std::cout << " }" << std::endl;
  }
}

/**
 * Función GenerateRandomNumbers
 * @brief Función que dado un tamaño n, genera n elementos aleatorios entre el 1000 y el 9999
 * @param sequence_size : tamño de la sequencia
 */
template <class Key>
std::vector<Key> GenerateRandomNumbers(const int sequence_size) {
  srand(time(NULL));
  std::vector<Key> result;
  for (int i = 0; i < sequence_size; i++) {
    result.push_back((rand() % 9000) + 1000);
  }
  return result;
}

/**
 * Función EnterSequenceNumbers
 * @brief Función que dado un tamaño n, pide tantos números por pantalla como sean necesarios
 * @param sequence_size : tamño de la sequencia
 */
template <class Key>
std::vector<Key> EnterSequenceNumbers(const int sequence_size) {
  std::vector<Key> result;
  for (int i = 0; i < sequence_size; i++) {
    system("clear");
    Key value;
    std::cout << "Introduce un valor : ";
    std::cin >> value;
    result.push_back(value);
  }
  return result;
}