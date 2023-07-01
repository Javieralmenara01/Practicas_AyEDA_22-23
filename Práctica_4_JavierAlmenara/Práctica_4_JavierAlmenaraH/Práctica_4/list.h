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
 * @file: list.h
 *    Clase que permite definir un tipo de dato abstracto denominado list
 */

#pragma once

#include "sequence.h"
#include <list>

/**
 * @brief Clase Lista
 * Clase derivada de la clase Sequence
 */
template <class Key>
class List : public Sequence<Key> {
 public:
  List() {}
  std::list<Key> list() const { return list_; }
  bool search(const Key& k) const override;
  bool insert(const Key& k) override;
  bool isFull() const override;
  void operator=(const Key& k);
 public:
  std::list<Key> list_;
};

/**
 * @brief Método Search permite buscar en la lista
 * @param k : clave k ha insertar
 */
template <class Key>
inline bool List<Key>::search(const Key& k) const {
  auto it = std::find(list_.begin(), list_.end(), k);
  usleep(100000);
  if (it != list_.end()) {
    return true;
  } else {
    return false;
  }
  return false;
}

/**
 * @brief Método Insert permite insertar en la lista 
 * @param k : clave k ha insertar
 */
template <class Key>
inline bool List<Key>::insert(const Key& k) {
  if (search(k)) {
    return false;
  } else {
    if (list_.size() > 0) {
      std::cout << "Se ha producido una colisión!" << std::endl;
    }
    list_.insert(list_.end(), k);
    return true;
  }
  return false;
}

/**
 * @brief Método isFull nos permite determinar si la lista
 */
template <class Key>
inline bool List<Key>::isFull() const {
  return false;
}

/**
 * @brief Sobrecarga del operador =
 * @param k : clave k
 */
template <class Key>
void List<Key>::operator=(const Key& k) {
  list_ = k.list();
}