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
 * @file: mergesort.h
 *    Clase que permite definir un tipo de dato denominado MergeSort
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include "sortmethod.h"
#include "library.h"

/**
 * Clase MergeSort 
 * @brief Implementación de la clase MergeSort, que emplea el algoritmo de ordenación MergeSort
 */
template<class Key, bool condition = false> 
class MergeSort : public SortMethod<Key> {
 public:
  MergeSort(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector
 */
template<class Key, bool condition>
void MergeSort<Key, condition>::Sort() {
  MergeSortFunction(SortMethod<Key>::seq_, 0, SortMethod<Key>::size_ - 1);
}

/**
 * Clase MergeSort 
 * @brief Implementación de la clase MergeSort, que emplea el algoritmo de ordenación MergeSort
 *        si se quiere utilizar el método con traza
 */
template<class Key> 
class MergeSort<Key, true> : public SortMethod<Key> {
 public:
  MergeSort(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector, mostrando la traza
 */
template<class Key>
void MergeSort<Key, true>::Sort() {
  MergeSortFunctionTrace(SortMethod<Key>::seq_, 0, SortMethod<Key>::size_ - 1);
}