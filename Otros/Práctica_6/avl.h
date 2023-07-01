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
 * @file: avl.h
 *  Clase que permite definir un tipo de dato denominado árbol balanceado
 */

#pragma once

#include "abb.h"
#include "nodoavl.h"

/// Macro que permite activar la traza de la clase AVL
//#define M_TRAZA

/**
 * @brief Clase que permite definir un tipo de dato denominado árbol balanceado
 */
template<class Key>
class AVL : public ABB<Key> {
 public :
  AVL(NodoAVL<Key>* raiz = nullptr) : ABB<Key>(raiz) {}
  bool insertar(const Key& k);
  NodoAVL<Key>* raiz() const { return reinterpret_cast<NodoAVL<Key>*>(AB<Key>::raiz_); }
  NodoAVL<Key>*& raiz() { return reinterpret_cast<NodoAVL<Key>*&>(AB<Key>::raiz_); }
 private :
  void inserta_bal_(NodoAVL<Key>* &nodo, NodoAVL<Key>* nuevo, bool& crece);
  void rotacion_II(NodoAVL<Key>* &nodo);
  void rotacion_DD(NodoAVL<Key>* &nodo);
  void rotacion_ID(NodoAVL<Key>* &nodo);
  void rotacion_DI(NodoAVL<Key>* &nodo);
  void insert_re_balancea_izda(NodoAVL<Key>* &nodo, bool& crece);
  void insert_re_balancea_dcha (NodoAVL<Key>* &nodo, bool& crece);
};

/**
 * @brief Función que permite insertar un elemento en el árbol balanceado
 * @param k Elemento a insertar
 * @return true si se ha insertado correctamente, false en caso contrario
 */
template<class Key>
bool AVL<Key>::insertar(const Key& k) {
  if (ABB<Key>::buscar(k)) {
    return false;
  }
  NodoAVL<Key>* nuevo = new NodoAVL<Key>(k);
  bool crece = false;
  inserta_bal_(raiz(), nuevo, crece);
  return true;
} 

/**
 * @brief Función que permite insertar un elemento en el árbol balanceado
 * @param nodo Nodo a partir del cual se va a insertar el elemento
 * @param nuevo Elemento a insertar
 * @param crece Variable que indica si el árbol ha crecido o no
 */
template<class Key>
void AVL<Key>::inserta_bal_(NodoAVL<Key>* &nodo, NodoAVL<Key>* nuevo, bool& crece) {
  if (nodo == nullptr) {
    nodo = nuevo;
    crece = true;
  } else if (nuevo->dato() < nodo->dato()) {
    inserta_bal_(nodo->izdo(), nuevo, crece);
    if (crece) {
      insert_re_balancea_izda(nodo, crece);
    }
  } else {
    inserta_bal_(nodo->dcho(), nuevo, crece);
    if (crece) { 
      insert_re_balancea_dcha(nodo, crece);
    }
  }
}

/**
 * @brief Función que permite insertar un elemento en el árbol balanceado meidante una rotación II
 * @param nodo Nodo a partir del cual se va a insertar el elemento
 */
template<class Key>
void AVL<Key>::rotacion_II(NodoAVL<Key>* &nodo) {
  NodoAVL<Key>* nodo1 = nodo->izdo();
  nodo->set_izdo(nodo1->dcho());
  nodo1->set_dcho(nodo);
  if (nodo1->bal() == 1) {
    nodo->set_bal(0);
    nodo1->set_bal(0);
  } else { // nodo1->bal_ == 0
    nodo->set_bal(1);
    nodo1->set_bal(-1);
  }
  nodo = nodo1;
}

/**
 * @brief Función que permite insertar un elemento en el árbol balanceado mediante una rotación DD
 * @param nodo Nodo a partir del cual se va a insertar el elemento
 */
template<class Key>
void AVL<Key>::rotacion_DD(NodoAVL<Key>* &nodo) {
  NodoAVL<Key>* nodo1 = nodo->dcho();
  nodo->set_dcho(nodo1->izdo());
  nodo1->set_izdo(nodo);
  if (nodo1->bal() == -1) {
    nodo->set_bal(0);
    nodo1->set_bal(0);
  } else { // nodo1->bal() == 0
    nodo->set_bal(-1);
    nodo1->set_bal(1);
  }
  nodo = nodo1; 
}

/**
 * @brief Función que permite insertar un elemento en el árbol balanceado mediante una rotación DI
 * @param nodo Nodo a partir del cual se va a insertar el elemento
 */
template<class Key>
void AVL<Key>::rotacion_ID(NodoAVL<Key>* &nodo) {
  NodoAVL<Key>* nodo1 = nodo->izdo();
  NodoAVL<Key>* nodo2 = nodo1->dcho();
  nodo->set_izdo(nodo2->dcho());
  nodo2->set_dcho(nodo);
  nodo1->set_dcho(nodo2->izdo());
  nodo2->set_izdo(nodo1);
  if (nodo2->bal() == 1)
    nodo1->set_bal(-1);
  else nodo1->set_bal(0);
  if (nodo2->bal() == -1)
    nodo->set_bal(1);
  else nodo->set_bal(0);
  nodo2->set_bal(0);
  nodo = nodo2;
}

/**
 * @brief Función que permite insertar un elemento en el árbol balanceado mediante una rotación ID
 *  @param nodo Nodo a partir del cual se va a insertar el elemento
*/
template<class Key>
void AVL<Key>::rotacion_DI(NodoAVL<Key>* &nodo) {
  NodoAVL<Key>* nodo1 = nodo->dcho();
  NodoAVL<Key>* nodo2 = nodo1->izdo();
  nodo->set_dcho(nodo2->izdo());
  nodo2->set_izdo(nodo);
  nodo1->set_izdo(nodo2->dcho());
  nodo2->set_dcho(nodo1);
  if (nodo2->bal() == -1)
    nodo1->set_bal(1);
  else nodo1->set_bal(0);
  if (nodo2->bal() == 1)
    nodo->set_bal(-1);
  else nodo->set_bal(0);
  nodo2->set_bal(0);
  nodo = nodo2;
}

/**
 * @brief Función que permite insertar un elemento en el árbol balanceado cuando el árbol crece por la izquierda
 * @param nodo Nodo a partir del cual se va a insertar el elemento
 * @param crece Variable que indica si el árbol ha crecido o no
 */
template<class Key>
void AVL<Key>::insert_re_balancea_izda(NodoAVL<Key>* &nodo, bool& crece) {
  switch (nodo->bal()) {
    case -1: {
      nodo->set_bal(0);
      crece = false;
      break; 
    } case 0: {
      nodo->set_bal(1);
      break; 
    } case 1: { 
      NodoAVL<Key>* nodo1 = (nodo->izdo());
      #ifdef M_TRAZA
        std::cout << BLCK "\nRebalanceo :" NC<< *this;
      #endif
      if (nodo1->bal() == 1) {
        #ifdef M_TRAZA
          std::cout << BLCK "\nRotación II en [" << nodo->dato() << "]:" NC;
        #endif
        rotacion_II(nodo);
      } else { 
        #ifdef M_TRAZA
          std::cout << BLCK "\nRotación ID en [" << nodo->dato() << "]:" NC;
        #endif
        rotacion_ID(nodo);
        crece = false;
      }
    }
  }
}

/**
 * @brief Función que permite insertar un elemento en el árbol balanceado cuando el árbol crece por la derecha
 * @param nodo Nodo a partir del cual se va a insertar el elemento
 * @param crece Variable que indica si el árbol ha crecido o no
 */
template<class Key>
void AVL<Key>::insert_re_balancea_dcha (NodoAVL<Key>* &nodo, bool& crece) {
  switch (nodo->bal()) {
    case 1: {
      nodo->set_bal(0);
      crece = false;
      break; 
    } case 0: {
      nodo->set_bal(-1);
      break; 
    } case -1: {
      NodoAVL<Key>* nodo1 = nodo->dcho();
      #ifdef M_TRAZA
        std::cout << BLCK "\nRebalanceo :" NC << *this;
      #endif
      if (nodo1->bal() == -1) {
        #ifdef M_TRAZA
          std::cout << BLCK "\nRotación DD en [" << nodo->dato() << "]:" NC;
        #endif
        rotacion_DD(nodo);
      } else {
        #ifdef M_TRAZA
          std::cout << BLCK "\nRotación DI en [" << nodo->dato() << "]:" NC;
        #endif
        rotacion_DI(nodo);
        crece = false;
      }
    }
  }
}