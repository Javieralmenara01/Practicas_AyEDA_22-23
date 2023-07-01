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

/**
 * Clase SortMethod
 * @brief La clase SortMethod permite utilizar el poliformimso dinámico y la herencia para poder usar diferentes
 *        métodos de ordenación 
 */
template<class Key> 
class SortMethod {
 public:
  SortMethod(const std::vector<Key>& seq, const unsigned size) : seq_(seq), size_(size) {}
  virtual void Sort() = 0;
  void Print();
 protected:
  unsigned size_;
  std::vector<Key> seq_;
};

/**
 * Método Sort
 * @brief Método que permite mostrar pon pantalla la sequencia almacenada
 */
template<class Key>
void SortMethod<Key>::Print() {
  std::cout << "{";
  for (auto it : SortMethod<Key>::seq_) {
    std::cout << " " << it << ",";
  }
  std::cout << "\b" << " }" << std::endl;
}