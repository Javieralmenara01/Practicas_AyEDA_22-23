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
 * @file: nodoavl.h
 *    Clase que permite definir un tipo de dato denominado nodo avl
 */

#pragma once 

#include "nodob.h"

/**
 * @brief Clase que permite definir un tipo de dato denominado nodo avl
 */
template<class Key>
class NodoAVL : public NodoB<Key> {
 public :
  NodoAVL(const Key& dato, const int bal = 0, NodoB<Key>* izdo = nullptr, NodoB<Key>* dcho = nullptr) : NodoB<Key>(dato, izdo, dcho), bal_(bal) {}
  int bal() const { return bal_; }
  void set_bal(const int bal) { bal_ = bal; }
  NodoAVL<Key>* izdo() const { return reinterpret_cast<NodoAVL<Key>*>(NodoB<Key>::izdo()); }
  NodoAVL<Key>* dcho() const { return reinterpret_cast<NodoAVL<Key>*>(NodoB<Key>::dcho()); }
  NodoAVL<Key>*& izdo() { return reinterpret_cast<NodoAVL<Key>*&>(NodoB<Key>::izdo()); }
  NodoAVL<Key>*& dcho() { return reinterpret_cast<NodoAVL<Key>*&>(NodoB<Key>::dcho()); }
  void set_izdo(NodoAVL<Key>* nodo) { NodoB<Key>::set_izdo(reinterpret_cast<NodoB<Key>*>(nodo)); }
  void set_dcho(NodoAVL<Key>* nodo) { NodoB<Key>::set_dcho(reinterpret_cast<NodoB<Key>*>(nodo)); }
 private : 
  int bal_;
};