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
 * @date: 01/03/2023
 * @file: block.h
 *    Clase que permite definir un tipo de dato abstracto denominado block
 */

#pragma once

#include "sequence.h"
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Clase Block
 * Clase derivada de la clase Sequence
 */
template <class Key>
class Block : public Sequence<Key> {
 public:
  Block() : blockSize_{1} { comparisons_ = 0; }
  Block(const size_t blockSize);
  bool search(const Key& k) override;
  bool insert(const Key& k) override;
  bool isFull() override;
  void operator=(const Key& k);
  unsigned getComparisons() const override { return comparisons_; }
  void restartComparisons() { comparisons_ = 0; }
 protected:
  void incrementComparisons() { ++comparisons_; }
 private:
  size_t blockSize_;
  size_t blockIterator_;
  Key* block_;
  unsigned comparisons_;
};

/**
 * @brief Constructor
 * @param blockSize : Size of the block
 */
template <class Key>
inline Block<Key>::Block(const size_t blockSize) {
  blockSize_ = blockSize;
  block_ = new Key[blockSize];
  blockIterator_ = 0;
}

/**
 * @brief Método Search permite buscar en el bloque
 * @param k : clave k ha insertar
 */
template <class Key>
inline bool Block<Key>::search(const Key& k) {
  restartComparisons();
  for (int i = 0; i <= blockIterator_; i++) {
    incrementComparisons();
    if (block_[i] == k) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Método Insert permite insertar en el bloque 
 * @param k : clave k ha insertar
 */
template <class Key>
inline bool Block<Key>::insert(const Key& k) {
  if (isFull()) {
    return false;
  } else if (search(k)) {
    return false;
  } else {
    if (blockIterator_ > 0) {
    }
    block_[blockIterator_] = k;
    blockIterator_++;
    return true;
  }
}

/**
 * @brief Método isFull nos permite determinar si el bloque está lleno
 */
template <class Key>
inline bool Block<Key>::isFull() {
  return blockIterator_ == blockSize_;
}

/**
 * @brief Sobrecarga del operador =
 * @param k : clave k
 */
template <class Key>
void Block<Key>::operator=(const Key& k) {
  block_ = k.block_;
  blockSize_ = k.blockSize_;
  blockIterator_ = k.blockIterator_;
}
