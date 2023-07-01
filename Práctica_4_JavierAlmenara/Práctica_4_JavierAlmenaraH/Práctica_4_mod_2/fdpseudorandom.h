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
 * @file: fdpseudorandom.h
 *    Clase abstracta que encapsula comportamiento
 */

#pragma once

#include "dispersionfunction.h"
#include <random>

/**
 * @brief Clase PseudoRandom derivada de Funcion de Dispersión
 */
template<class Key>
class fdPseudoRandom : public DispersionFunction<Key> {
 public:
  fdPseudoRandom(const unsigned n) : tableSize(n) {} 
  unsigned operator()(const Key& k) const {
    srand(k);
    return rand() % tableSize; 
  }
 private:
  unsigned tableSize;
};