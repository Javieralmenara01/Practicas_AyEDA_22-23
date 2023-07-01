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
 * @file: radixsort.h
 *    Clase que permite definir un tipo de dato denominado RadixSort
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include "sortmethod.h"
#include "library.h"

/**
 * Clase RadixSort 
 * @brief Implementación de la clase RadixSort, que emplea el algoritmo de ordenación RadixSort
 */
template<class Key, bool condition = false> 
class RadixSort : public SortMethod<Key> {
 public:
  RadixSort(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector
 */
template<class Key, bool condition>
void RadixSort<Key, condition>::Sort() {
  RadixSortFunction(SortMethod<Key>::seq_, SortMethod<Key>::size_);
}

/**
 * Clase RadixSort 
 * @brief Implementación de la clase RadixSort, que emplea el algoritmo de ordenación RadixSort
 *        si se quiere utilizar el método con traza
 */
template<class Key>
class RadixSort<Key, true> : public SortMethod<Key> {
 public:
  RadixSort(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector, mostrando la traza
 */
template<class Key>
void RadixSort<Key, true>::Sort() {
  RadixSortFunctionTrace(SortMethod<Key>::seq_, SortMethod<Key>::size_);
}