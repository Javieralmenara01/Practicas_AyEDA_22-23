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
 * @file: fdsum.h
 *    Clase abstracta que encapsula comportamiento
 */

#pragma once

#include "dispersionfunction.h"

/**
 * @brief Clase Suma derivada de Funcion de Dispersión
 */
template<class Key>
class fdSum : public DispersionFunction<Key> {
 public:
  fdSum(const unsigned n) : tableSize(n) {} 
  unsigned operator()(const Key& k) const {
    unsigned sum = 0, duplicated_key = (unsigned)k;
    while (duplicated_key != 0) {
      sum += (unsigned)duplicated_key % 10;
      duplicated_key = duplicated_key / 10;
    }
    return sum; 
  }
 private:
  unsigned tableSize;
};