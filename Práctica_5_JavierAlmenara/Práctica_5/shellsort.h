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
 * @file: shellsort.h
 *    Clase que permite definir un tipo de dato denominado ShellSort
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include "sortmethod.h"
#include "library.h"

/**
 * Clase ShellSort 
 * @brief Implementación de la clase ShellSort, que emplea el algoritmo de ordenación ShellSort
 *        si se quiere utilizar el método con traza
 */
template<class Key, bool condition = false> 
class ShellSort : public SortMethod<Key> {
 public:
  ShellSort(const std::vector<Key>& seq, const unsigned size, const double alpha) : SortMethod<Key>(seq, size), alpha_{alpha} {}
  void Sort() override;
 private:
  double alpha_;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector
 */
template<class Key, bool condition>
void ShellSort<Key, condition>::Sort() {
  ShellSortFunction(SortMethod<Key>::seq_, SortMethod<Key>::size_, alpha_);
}

/**
 * Clase ShellSort 
 * @brief Implementación de la clase ShellSort, que emplea el algoritmo de ordenación ShellSort
 *        si se quiere utilizar el método con traza
 */
template<class Key> 
class ShellSort<Key, true> : public SortMethod<Key> {
 public:
  ShellSort(const std::vector<Key>& seq, const unsigned size, const double alpha) : SortMethod<Key>(seq, size), alpha_{alpha} {}
  void Sort() override;
 private:
  double alpha_;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector, mostrando la traza
 */
template<class Key>
void ShellSort<Key, true>::Sort() {
  ShellSortFunctionTrace(SortMethod<Key>::seq_, SortMethod<Key>::size_, alpha_);
}