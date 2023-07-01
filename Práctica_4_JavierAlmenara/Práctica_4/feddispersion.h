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

/**
 * @brief Clase DobleDispersión derivada de Funcion de Exploracióm
 */
template<class Key>
class feDDispersion : public ExplorationFunction<Key> {
 public:
  feDDispersion(DispersionFunction<Key>* function) : function_{function} {}
  unsigned operator()(const Key& k, unsigned i) const override { return (*function_)(k) * i; }
 private:
  DispersionFunction<Key>* function_;
};