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
 * @file: radixsort.h
 *    Clase que permite definir un tipo de dato denominado RadixSort
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include "sortmethod.h"

template<class Key> 
class RadixSort : public SortMethod<Key> {
 public:
  RadixSort(const std::vector<Key>& seq, const unsigned size) : seq_{seq}, size_{size} {}
  void Sort() override;
  void Print() override;
 private:
  unsigned size_;
  std::vector<Key> seq_;
};

template <typename T>
T getMax(std::vector<T> seq, int n) {
  T max = seq[0];
  for (int i = 1; i < n; i++) {
    if (seq[i] > max) {
      max = seq[i];
    }
  }
  return max;
}

template<class Key> 
void RadixSort<Key>::Sort() {
  // Inicializamos el arreglo que contendrá los elementos
  std::vector<Key> output(size_);
  // Obtenemos el máximo elemento
  Key max_element = getMax(seq_, size_);
  // Realizamos la cuenta de los elementos para cada dígito
  for (Key exp = 1; max_element / exp > 0; exp *= 10) {
    std::vector<int> count(10, 0);
    for (int i = 0; i < size_; i++) {
      count[(seq_[i] / exp) % 10]++;
    }

    // Calculamos las posiciones finales de cada dígito
    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }

    // Colocamos los elementos en su posición final
    for (int i = size_ - 1; i >= 0; i--) {
      output[count[(seq_[i] / exp) % 10] - 1] = seq_[i];
      count[(seq_[i] / exp) % 10]--;
    }

    // Copiamos el vector ordenado al vector original
    for (int i = 0; i < size_; i++) {
      seq_[i] = output[i];
    }
  }
}

template<class Key> 
void RadixSort<Key>::Print() {
  std::cout << "{";
  for (auto it : seq_) {
    std::cout << " " << it << ",";
  }
  std::cout << "\b" << "}" << std::endl;
}