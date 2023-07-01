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
  StartProgram();
  unsigned arbol_option = ObtainTree(), empty_tree = 0;
  AB<long>* arbol;
  switch(arbol_option) {
    case 1: {
      arbol = new ABB<long>();
      break;
    } case 2: {
      arbol = new AVL<long>();
      break;
    }
  }
  bool program_on = true;
  while (program_on) {
    unsigned option = ObtainOption();
    if (empty_tree == 0) {
      std::cout << BLCK "Árbol Vacío" NC << *arbol << std::endl << std::endl;
      empty_tree++;
    }
    switch(option) {
      case 1 : {
        long clave;
        std::cout << "Introduzca el valor a introducir : ";
        std::cin >> clave;
        std::cout << BLCK "\nInsertar: " NC << clave; 
        if (arbol->insertar(clave)) {
          std::cout << *arbol << std::endl;
          std::cout << GRN "Valor insertado!" NC << std::endl;
          usleep(1000000);
        } else {
          std::cout << *arbol << std::endl;
          std::cout << RED "Valor no insertado!" NC << std::endl;
          usleep(1000000);
        }
        usleep(4000000);
        break;
      } case 2 : {
        long clave;
        std::cout << "Introduzca el valor a buscar : ";
        std::cin >> clave;
        if (arbol->buscar(clave)) {
          std::cout << GRN "Clave encontrada!" NC << std::endl;
          usleep(1000000);
        } else {
          std::cout << RED "Clave no encontrada!" NC << std::endl;
          usleep(1000000);
        }
        std::cout << *arbol << std::endl;
        usleep(4000000);
        break;
      } case 3 : {
        arbol->preorden();
        std::fflush(stdout);
        usleep(4000000);
        break;
      } case 4 : {
        arbol->inorden();
        std::fflush(stdout);
        usleep(4000000);
        break;
      } case 5 : {
        arbol->postorden();
        std::fflush(stdout);
        usleep(4000000);
        break;
      } case 0 : {
        return 0;
        break;
      }
    }
  }
  return 0;
}