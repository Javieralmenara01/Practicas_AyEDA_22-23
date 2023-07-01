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
 * @file: nodo.h
 *    Clase que permite definir un tipo de dato denominado nodo
 */

#pragma once 

/**
 * @brief Clase que permite definir un tipo de dato denominado nodo
 */
template<class Key>
class NodoB {
 public :
  NodoB(const int dato, NodoB<Key>* izdo = nullptr, NodoB<Key>* dcho = nullptr) : dato_(dato), izdo_(izdo), dcho_(dcho) {}
  Key dato() const { return dato_; } 
  NodoB<Key>* izdo() const { return izdo_; }
  NodoB<Key>* dcho() const { return dcho_; }
  NodoB<Key>*& izdo() { return izdo_; }
  NodoB<Key>*& dcho() { return dcho_; }
  void set_izdo(NodoB<Key>* nodo) { izdo_ = nodo; }
  void set_dcho(NodoB<Key>* nodo) { dcho_ = nodo; }
 private: 
  Key dato_;
  NodoB<Key>* izdo_;
  NodoB<Key>* dcho_;
};