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
 * @file: client.cc
 *    Programa cliente
 */

#include "ab.h"
#include "abb.h"
#include "avl.h"
#include "functions.h"
#include "nodoavl.h"
#include "nodob.h"

/**
 * @brief Función main que permite iniciar el programa
 */
int main() {
  AB<long>* arbol1;
  AB<long>* arbol2;
  arbol1 = new ABB<long>();
  for (int i = 0; i < 5000; i++) {
    arbol1->insertar(rand() % 50000);
  }
  arbol1->contar_nodos();
  std::cout << "ABB Nº de nodos en el subárbol izquierdo: " << arbol1->nodos_izq() << "\n";
  std::cout << "ABB Nº de nodos en el subárbol derecho: " << arbol1->nodos_der() << "\n";
  arbol2 = new AVL<long>();
  for (int i = 0; i < 5000; i++) {
    arbol2->insertar(rand() % 50000);
  }
  arbol2->contar_nodos();
  std::cout << "AVL Nº de nodos en el subárbol izquierdo: " << arbol2->nodos_izq() << "\n";
  std::cout << "AVL Nº de nodos en el subárbol derecho: " << arbol2->nodos_der() << "\n";
  std::cout << "\n ¿Cuantos valores desea buscar?" << std::endl;
  int n;
  std::cin >> n;
  while(n-- != 0) {
    long clave;
    std::cout << "Introduzca el valor a buscar : ";
    std::cin >> clave;
    if (arbol2->buscar(clave)) {
      std::cout << GRN "Clave encontrada!" NC << std::endl;
      usleep(1000000);
    } else {
      std::cout << RED "Clave no encontrada!" NC << std::endl;
      usleep(1000000);
    }
  }
  return 0;
}