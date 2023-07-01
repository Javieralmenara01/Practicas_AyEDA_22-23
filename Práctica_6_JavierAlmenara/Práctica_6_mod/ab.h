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
  virtual int nodos_izq() const = 0;
  virtual int nodos_der() const = 0;
  void inorden() const; 
  void preorden() const;
  void postorden() const;
  virtual void contar_nodos() = 0;
  friend std::ostream& operator<<<>(std::ostream& os, const AB<Key>& arbol);
 protected : 
  NodoB<Key>* raiz_;
};

/**
 * @brief Función que permite recorrer el árbol binario en preorden
 */
template<class Key>
void AB<Key>::preorden() const {
  std::cout << "Recorrido PreOrden : ";
  recorre_preorden(raiz_);
}

/**
 * @brief Función que permite recorrer el árbol binario en preorden
 * @param nodo Nodo a partir del cual se va a recorrer el árbol
 */
template<class Key>
void recorre_preorden(NodoB<Key> *nodo) {
  if (nodo == NULL) return;
  std::cout << nodo->dato() << " ";
  recorre_preorden(nodo->izdo());
  recorre_preorden(nodo->dcho());
}

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
 * @brief Función que permite recorrer el árbol binario en postorden
 */
template<class Key>
void AB<Key>::postorden() const {
  std::cout << "Recorrido PostOrden : ";
  recorre_postorden(raiz_);
}

/**
 * @brief Función que permite recorrer el árbol binario en postorden
 * @param nodo Nodo a partir del cual se va a recorrer el árbol
 */
template<class Key>
void recorre_postorden(NodoB<Key> *nodo) {
  if (nodo == NULL) return;
  recorre_postorden(nodo->izdo());
  recorre_postorden(nodo->dcho());
  std::cout << nodo->dato() << " ";
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
    int nivel = nodos.front();
    nodos.pop();
    if (nivel != nivel_actual) {
      nivel_actual = nivel;
      usleep(100000);
      os << BLCK "\nNivel " << nivel_actual << ": " NC;
    }
    if (nodo != nullptr) {
      os << "[" << nodo->dato() << "] ";
      nodos.push(nodo->izdo());
      nodos.push(nodo->dcho());
    } else { 
      os << "[·] ";
    }
  }
}

