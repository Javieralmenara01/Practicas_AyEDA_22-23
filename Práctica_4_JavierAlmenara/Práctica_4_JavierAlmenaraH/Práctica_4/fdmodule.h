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
 * @file: fdmodule.h
 *    Clase abstracta que encapsula comportamiento
 */

#pragma once

#include "dispersionfunction.h"

/**
 * @brief Clase Módulo derivada de Funcion de Dispersión
 */
template<class Key>
class fdModule : public DispersionFunction<Key> {
 public:
  fdModule(const unsigned n) : tableSize(n) {} 
  unsigned operator()(const Key& k) const {
    usleep(300000);
    return k % tableSize; 
  }
 private:
  unsigned tableSize;
};