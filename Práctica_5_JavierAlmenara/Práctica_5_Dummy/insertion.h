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
 * @file: insertion.h
 *    Clase que permite definir un tipo de dato denominado Insertion
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include "sortmethod.h"
#include "library.h"

/**
 * Clase Insertion 
 * @brief Implementación de la clase Insertion, que emplea el algoritmo de ordenación por inserción
 */
template<class Key, bool condition = false> 
class Insertion : public SortMethod<Key> {
 public:
  Insertion(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector
 */
template<class Key, bool condition>
void Insertion<Key, condition>::Sort() {
  InsertionFunction(SortMethod<Key>::seq_, SortMethod<Key>::size_);
}

/**
 * Clase Insertion 
 * @brief Implementación de la clase Insertion, que emplea el algoritmo de ordenación por inserción
 *        si se quiere utilizar el método con traza
 */
template<class Key> 
class Insertion<Key, true> : public SortMethod<Key> {
 public:
  Insertion(const std::vector<Key>& seq, const unsigned size) : SortMethod<Key>(seq, size) {}
  void Sort() override;
};

/**
 * Método Sort
 * @brief Método que permite ordenar un vector, mostrando la traza
 */
template<class Key>
void Insertion<Key, true>::Sort() {
  InsertionFunctionTrace(SortMethod<Key>::seq_, SortMethod<Key>::size_);
}