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
 * @file: heapsort.h
 *    Clase que permite definir un tipo de dato denominado HeapSort
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include <algorithm>
#include "sortmethod.h"

template<class Key> 
class HeapSort : public SortMethod<Key> {
 public:
  HeapSort(const std::vector<Key>& seq, const unsigned size) : seq_{seq}, size_{size} {}
  void Sort() override;
  void Print() override;
 private:
  unsigned size_;
  std::vector<Key> seq_;
};

template<class Key> 
void baja(int i, std::vector<Key>& sec, int n) {
   while (2 * i <= n) {
    int h1 = 2 * i, h;
    int h2 = h1 + 1;
    if (h1 == n) {
      h = h1;
    } else if (sec[h1] > sec[h2]) {
      h = h1;
    } else {
      h = h2;
    }
    if (sec[h] <= sec[i]) {
      break ; 
    } else {
      std::swap(sec[i],sec[h]) ;
      i = h;
    }
   }
}


template<class Key> 
void HeapSort<Key>::Sort() {
  for (int i = (size_ / 2); i >= 0; i--) {
    baja(i, seq_, size_);
  }
  for (int i = size_ - 1; i > 0; i--) {
    std::swap(seq_[0], seq_[i]);
    baja(0, seq_, i - 1) ;
  }
}

template<class Key> 
void HeapSort<Key>::Print() {
  std::cout << "{";
  for (auto it : seq_) {
    std::cout << " " << it << ",";
  }
  std::cout << "\b" << "}" << std::endl;
}