/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 6: Implementación del TDA Árbol
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 19/04/2023
 * @file: ab.h
 *    Clase que permite definir un tipo de dato denominado árbol binario
 */

#pragma once

#include <iostream>
#include <queue>
#include "nodob.h"
#include "functions.h"

/**
 * @brief Clase abstracta que permite definir un tipo de dato denominado árbol binario
 */
template<class Key>
class AB {
 public :
  AB(NodoB<Key>* raiz = nullptr) : raiz_(raiz) {}
  virtual bool insertar(const Key& k) = 0;
  virtual bool buscar(const Key& k) const = 0;
  void inorden() const; 
  friend std::ostream& operator<<<>(std::ostream& os, const AB<Key>& arbol);
 protected : 
  NodoB<Key>* raiz_;
};

/**
 * @brief Función que permite recorrer el árbol binario en inorden
 */
template<class Key>
void AB<Key>::inorden() const {
  std::cout << "Recorrido Inorden : ";
  recorre_inorden(raiz_);
}

/**
 * @brief Función que permite recorrer el árbol binario en inorden
 * @param nodo Nodo a partir del cual se va a recorrer el árbol
 */
template<class Key>
void recorre_inorden(NodoB<Key> *nodo) {
  if (nodo == nullptr) return;
  recorre_inorden(nodo->izdo());
  std::cout << nodo->dato() << " ";
  recorre_inorden(nodo->dcho());
}

/**
 * @brief Sobrecarga del operador << para poder imprimir el árbol binario
 * @param os Flujo de salida
 * @param arbol Árbol binario a imprimir
 * @return Devuelve el flujo de salida
 */
template<class Key>
std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
  recorre_niveles(arbol.raiz_, os);
  return os;
}

/**
 * @brief Función que permite recorrer el árbol binario por niveles
 * @param nodo_raiz Nodo a partir del cual se va a recorrer el árbol
 * @param os Flujo de salida
 */
template<class Key>
void recorre_niveles(NodoB<Key> *nodo_raiz, std::ostream& os) {
  if (nodo_raiz == nullptr) {
    os << BLCK "\nNivel 0: [·]" NC;
    return;
  }
  std::queue<std::pair<NodoB<Key>*, int>> nodos;
  nodos.push({nodo_raiz, 0});
  int nivel_actual = -1;
  while (!nodos.empty()) {
    NodoB<Key>* nodo = nodos.front().first;
    int nivel = nodos.front().second;
    nodos.pop();
    if (nivel != nivel_actual) {
      nivel_actual = nivel;
      usleep(100000);
      os << BLCK "\nNivel " << nivel_actual << ": " NC;
    }
    if (nodo != nullptr) {
      os << "[" << nodo->dato() << "] ";
      nodos.push({nodo->izdo(), nivel + 1});
      nodos.push({nodo->dcho(), nivel + 1});
    } else { 
      os << "[·] ";
    }
  }
}