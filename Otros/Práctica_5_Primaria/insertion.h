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
 * @file: insertion.h
 *    Clase que permite definir un tipo de dato denominado Insertion
 *    con el fin de ordenar un vector de elementos.
 */

#pragma once

#include "sortmethod.h"

template<class Key> 
class Insertion : public SortMethod<Key> {
 public:
  Insertion(const std::vector<Key>& seq, const unsigned size) : seq_{seq}, size_{size} {}
  void Sort() override;
  void Print() override;
 private:
  unsigned size_;
  std::vector<Key> seq_;
};

template<class Key> 
void Insertion<Key>::Sort() {
  for (int i = 0; i < size_; i++) { 
    int j = i;
    Key x = seq_[i];
    while ((x < seq_[j - 1]) && (j - 1 > 0)) {
      seq_[j] = seq_[j - 1];
      j--;
    } 
    seq_[j] = x;
  }
}

template<class Key> 
void Insertion<Key>::Print() {
  std::cout << "{";
  for (auto it : seq_) {
    std::cout << " " << it << ",";
  }
  std::cout << "\b" << "}" << std::endl;
}