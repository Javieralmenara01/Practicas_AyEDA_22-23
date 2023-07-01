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
 * @file: quicksort.h
 *    Clase que permite definir un tipo de dato denominado QuickSort
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include "sortmethod.h"
#include "library.h"

/**
 * Clase QuickSort 
 * @brief Implementación de la clase QuickSort, que emplea el algoritmo de ordenación QuickSort
 */
template<class Key, bool condition = false> 
class QuickSort : public SortMethod<Key> {
 public:
  QuickSort(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector
 */
template<class Key, bool condition>
void QuickSort<Key, condition>::Sort() {
  QuickSortFunction(SortMethod<Key>::seq_, 0, SortMethod<Key>::size_ - 1);
}

/**
 * Clase QuickSort 
 * @brief Implementación de la clase QuickSort, que emplea el algoritmo de ordenación QuickSort
 *        si se quiere utilizar el método con traza
 */
template<class Key> 
class QuickSort<Key, true> : public SortMethod<Key> {
 public:
  QuickSort(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector, mostrando la traza
 */
template<class Key>
void QuickSort<Key, true>::Sort() {
  QuickSortFunctionTrace(SortMethod<Key>::seq_, 0, SortMethod<Key>::size_ - 1);
}