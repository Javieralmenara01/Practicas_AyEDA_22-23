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
 * @file: shellsort.h
 *    Clase que permite definir un tipo de dato denominado ShellSort
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include "sortmethod.h"

template<class Key> 
class ShellSort : public SortMethod<Key> {
 public:
  ShellSort(const std::vector<Key>& seq, const unsigned size, const double alpha) : seq_{seq}, size_{size}, alpha_{alpha} {}
  void Sort() override;
  void Print() override;
 private:
  unsigned size_;
  std::vector<Key> seq_;
  double alpha_;
};

template<class Key> 
void DeltaSort(int delta, std::vector<Key>& sec, int n) {
  for (int i = delta; i < n; i++){
    Key x = sec[i] ;
    int j = i ;
    while ((j >= delta) && (x < sec[j - delta])){
      sec[j] = sec[j - delta] ;
      j = j - delta ;
    }
    sec[j] = x ;
  }
}

template<class Key> 
void ShellSort<Key>::Sort() {
  int delta = size_;
  while (delta > 1) {
    std::cout << delta << std::endl;
    delta = (double)delta * alpha_;
    DeltaSort(delta, seq_, (int)size_);
  }
}

template<class Key> 
void ShellSort<Key>::Print() {
  std::cout << "{";
  for (auto it : seq_) {
    std::cout << " " << it << ",";
  }
  std::cout << "\b" << "}" << std::endl;
}