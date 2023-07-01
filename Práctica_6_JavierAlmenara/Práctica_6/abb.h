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
 * @file: abb.h
 *   Clase que permite definir un tipo de dato denominado árbol binario de búsqueda
 */

#pragma once

#include "ab.h"
#include "nodob.h"

/**
 * @brief Clase que permite definir un tipo de dato denominado árbol binario de búsqueda
 */
template<class Key>
class ABB : public AB<Key> {
 public :
  ABB(NodoB<Key>* raiz = nullptr) : AB<Key>(raiz) {}
  bool insertar(const Key& k);
  bool buscar(const Key& k) const;
 private :
  void InsertarRama(NodoB<Key>* &nodo, const Key& clave_dada);
  bool BuscarRama(NodoB<Key>* nodo, const Key& clave_dada) const;
};

/**
 * @brief Función que permite insertar un elemento en el árbol binario de búsqueda  
 * @param k Elemento a insertar
 * @return true si se ha insertado correctamente, false en caso contrario
 * @note Esta función es recursiva
 */
template<class Key>
bool ABB<Key>::insertar(const Key& k) {
  if (buscar(k)) {
    return false;
  } else {
    InsertarRama(AB<Key>::raiz_, k);
    return true;
  }
  return true;
}

/**
 * @brief Función que permite insertar un elemento en el árbol binario de búsqueda
 * @param nodo Nodo a partir del cual se va a insertar el elemento
 * @param clave_dada Elemento a insertar
 * @return true si se ha insertado correctamente, false en caso contrario
 * @note Esta función es recursiva y privada
*/
template<class Key>
void ABB<Key>::InsertarRama(NodoB<Key>* &nodo, const Key& clave_dada) {
  if (nodo == NULL) {
    nodo = new NodoB<Key>(clave_dada);
  } else if (clave_dada < nodo->dato()) {
    InsertarRama(nodo->izdo(), clave_dada);
  } else {
    InsertarRama(nodo->dcho(), clave_dada); 
  }
} 

/**
 * @brief Función que permite buscar un elemento en el árbol binario de búsqueda
 * @param k Elemento a buscar
 * @return true si se ha encontrado el elemento, false en caso contrario
 * @note Esta función es recursiva
 */
template<class Key>
bool ABB<Key>::buscar(const Key& k) const {
  return BuscarRama(AB<Key>::raiz_, k);
}

/** 
 * @brief Función que permite buscar un elemento en el árbol binario de búsqueda
 * @param nodo Nodo a partir del cual se va a buscar el elemento
 * @param clave_dada Elemento a buscar
 * @return true si se ha encontrado el elemento, false en caso contrario
 * @note Esta función es recursiva y privada
 */
template<class Key>
bool ABB<Key>::BuscarRama(NodoB<Key>* nodo, const Key& clave_dada) const {
  if (nodo == NULL) {
    return false;
  }
  if (clave_dada == nodo->dato()) {
    return true;
  }
  if (clave_dada < nodo->dato()) {
    return BuscarRama(nodo->izdo(), clave_dada);
  }
  return BuscarRama(nodo->dcho(), clave_dada);
} 
