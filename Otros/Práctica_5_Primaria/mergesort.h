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
 * @file: mergesort.h
 *    Clase que permite definir un tipo de dato denominado MergeSort
 *    con el fin de ordenar un vector de elementos.
 */

#include "sortmethod.h"

#pragma once

template <class Key> 
class MergeSort : public SortMethod<Key> {
 public:
  MergeSort(const std::vector<Key>& seq, const unsigned size) : seq_{seq}, size_{size} {}
  void Sort() override;
  void Print() override;
 private:
  unsigned size_;
  std::vector<Key> seq_;
};

template <class Key>
void Mezcla(std::vector<Key>& sec, unsigned ini, unsigned cen, unsigned fin) {
  std::vector<Key> aux(fin + 1);
  unsigned i = ini, j = cen + 1;
  for (int k = ini; k <= fin; k++) {
    if (i > cen) {
      aux[k] = sec[j];
      j++;
    } else if (j > fin) {
      aux[k] = sec[i];
      i++;
    } else if (sec[i] < sec[j]) {
      aux[k] = sec[i];
      i++;
    } else {
      aux[k] = sec[j];
      j++;
    }
  }
  for (int k = ini; k <= fin; k++) {
    sec[k] = aux[k];
  }
} 

template <class Key>
void Msort(std::vector<Key>& sec, unsigned ini, unsigned fin) {
  if (ini < fin) {
    unsigned cen = (ini + fin) / 2;
    Msort(sec, ini, cen);
    Msort(sec, cen + 1, fin);
    Mezcla(sec, ini, cen, fin);
  } 
}

template <class Key>
void MergeSort<Key>::Sort() {
  Msort(seq_, 0, size_ - 1);
}

template<class Key> 
void MergeSort<Key>::Print() {
  std::cout << "{";
  for (auto it : seq_) {
    std::cout << " " << it << ",";
  }
  std::cout << "\b" << "}" << std::endl;
}