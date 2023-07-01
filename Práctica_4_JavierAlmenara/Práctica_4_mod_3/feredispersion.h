/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 4: Búsqueda por dispersión
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 11/03/2023
 * @file: feddispersion.h
 *    Clase abstracta que encapsula comportamiento
 */

#pragma once

#include "explorationfunction.h"
#include <random>

/**
 * @brief Clase ReDispersion derivada de Funcion de Exploracióm
 */
template<class Key>
class feRedispersion : public ExplorationFunction<Key> {
 public:
  feRedispersion() {}
  unsigned operator()(const Key& k, unsigned i) const { 
   Key final_key = k;
   for (unsigned j = 0; j < i; j++) {
     srand(final_key);
     final_key = rand();
   }
   return final_key;
  }
};