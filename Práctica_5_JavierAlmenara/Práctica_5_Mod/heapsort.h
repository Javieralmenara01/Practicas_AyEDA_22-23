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
 * @file: heapsort.h
 *    Clase que permite definir un tipo de dato denominado HeapSort
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include <algorithm>
#include "sortmethod.h"
#include "library.h"

/**
 * Clase HeapSort 
 * @brief Implementación de la clase HeapSort, que emplea el algoritmo de ordenación HeapSort  
 */
template<class Key, bool condition = false> 
class HeapSort : public SortMethod<Key> {
 public:
  HeapSort(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector
 */
template<class Key, bool condition>
void HeapSort<Key, condition>::Sort() {
  HeapSortFunction(SortMethod<Key>::seq_, SortMethod<Key>::size_);
}

/**
 * Clase HeapSort 
 * @brief Implementación de la clase HeapSort, que emplea el algoritmo de ordenación HeapSort
 *        si se quiere utilizar el método con traza
 */
template<class Key> 
class HeapSort<Key, true> : public SortMethod<Key> {
 public:
  HeapSort(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector, mostrando la traza
 */
template<class Key>
void HeapSort<Key, true>::Sort() {
  HeapSortFunctionTrace(SortMethod<Key>::seq_, SortMethod<Key>::size_);
}