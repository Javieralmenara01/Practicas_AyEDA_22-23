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
 * @file: sortmethod.h
 *    Clase que permite definir un puntero a un tipo de dato abstracto denominado SortMethod
 *    con el fin de usar el poliformismo dinámico.
 */

#pragma once

#include <vector>

template<class Key> 
class SortMethod {
 public:
  virtual void Sort( ) = 0;
  virtual void Print() = 0;
 private:
  unsigned size_;
  std::vector<Key> seq_;
};