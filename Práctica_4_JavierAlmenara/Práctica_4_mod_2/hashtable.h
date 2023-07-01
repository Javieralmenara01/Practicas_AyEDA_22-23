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
 * @file: hashtable.h
 *    Clase que permite definir un tipo de dato abstracto denominado tabla hash
 */

#pragma once

#include "block.h"
#include "dispersionfunction.h"
#include "explorationfunction.h"
#include "list.h"
#include "sequence.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * Clase HashTable
 */
template<class Key>
class HashTable {
 public:
  HashTable(size_t tableSize, DispersionFunction<Key>* fd, ExplorationFunction<Key>* fe = nullptr, size_t blockSize = 0);
  bool search(const Key& k);
  bool insert(const Key& k);
  size_t getTableSize() const { return tableSize_; }
  unsigned GetComparisons() const { return comparisons_; }
  void restartComparisons() { comparisons_ = 0; }
 private:
  size_t tableSize_;
  Sequence<Key>** table_;
  DispersionFunction<Key>* fd_;
  size_t blockSize_;
  ExplorationFunction<Key>* fe_;
  unsigned comparisons_;
};

/**
 * @brief Constructor
 * @param tableSize : tamaño de la tabla
 * @param fd : función de dispersión
 * @param fe : función de exploración
 * @param blockSize : tamaño del bloque
 */
template<class Key> 
HashTable<Key>::HashTable(size_t tableSize, DispersionFunction<Key>* fd, ExplorationFunction<Key>* fe, size_t blockSize) {
  tableSize_ = tableSize;
  fd_ = fd;
  if (fe == nullptr) {
    table_ = new Sequence<Key>*[tableSize];
    for (unsigned i = 0; i < tableSize; ++i) {
      table_[i] = new List<Key>();
    }
  } else {
    table_ = new Sequence<Key>*[tableSize];
    for (unsigned i = 0; i < tableSize; ++i) {
      table_[i] = new Block<Key>(blockSize);
    }
  }
  fe_ = fe;
  blockSize_ = blockSize;
  comparisons_ = 0;
}

/**
 * @brief Método Search permite buscar en la tabla
 * @param k : clave k
 */
template<class Key> 
bool HashTable<Key>::search(const Key& k) {
  const unsigned position = (*fd_)(k);
  const bool searching = table_[position]->search(k);
  comparisons_ += table_[position]->getComparisons();
  if (searching) {
    return true;
  } else if (!searching && !table_[position]->isFull()) {
    return false;
  } else {
    unsigned iterator_base = 0;
    while (iterator_base < tableSize_) {
      unsigned final_position = (((*fe_)(k, iterator_base) + position) % tableSize_);
      bool searching_2 = table_[final_position]->search(k);
      comparisons_ += table_[final_position]->getComparisons();
      if (searching_2) {
        return true;
      } else if (!searching_2 && !table_[final_position]->isFull()) {
        return false;
      }
      iterator_base++;
    }
  }
  return false;
}

/**
 * @brief Método Insert permite insertar en la tabla
 * @param k : clave k
 */
template<class Key> 
bool HashTable<Key>::insert(const Key& k) {
  const unsigned position = (*fd_)(k);
  if (table_[position]->insert(k)) {
    comparisons_ += table_[position]->getComparisons();
    return true;
  } else if (fe_ != nullptr && !table_[position]->search(k)) {
    unsigned iterator_base = 0;
    while (iterator_base < tableSize_) {
      unsigned final_position = (((*fe_)(k, iterator_base) + position) % tableSize_);
      if (table_[final_position]->insert(k)) {
        comparisons_ += table_[final_position]->getComparisons();
        return true;
      }
      if (table_[final_position]->search(k)) {
        comparisons_ += table_[position]->getComparisons();
        return false;
      }
      iterator_base++;
    }
  }
  return false;
}