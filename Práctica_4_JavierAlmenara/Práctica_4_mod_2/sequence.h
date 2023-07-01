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
 * @file: sequence.h
 *    Clase que permite definir un tipo de dato abstracto denominado sequence
 */

#pragma once

/**
 * Clase Abstracta Sequence
 */
template <class Key>
class Sequence {
 public:
  virtual bool search(const Key& k) = 0;
  virtual bool insert(const Key& k) = 0;
  virtual bool isFull() = 0;
  virtual unsigned getComparisons() const = 0;
};