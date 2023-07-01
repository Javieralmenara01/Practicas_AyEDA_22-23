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

/

template <class Key>
std::vector<Key> GenerateRandomNumbers(const int sequence_size) {
  srand(time(NULL));
  std::vector<Key> result;
  for (int i = 0; i < sequence_size; i++) {
    result.push_back((rand() % 9000) + 1000);
  }
  return result;
}

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