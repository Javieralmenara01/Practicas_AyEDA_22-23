/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 4: Búsqueda por dispersión
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 11/03/2023
 * @file: client.cc
 *    Programa cliente
 */

#include "block.h"
#include "fdmodule.h"
#include "fdpseudorandom.h"
#include "fdsum.h"
#include "feddispersion.h"
#include "felineal.h"
#include "fequadratic.h"
#include "feredispersion.h"
#include "hashtable.h"
#include "functions.h"
#include "list.h"

int main(int argc, char** argv) {
  StartProgram();
  size_t table_size = ObtainTableSize(), block_size = 0;
  unsigned option_fd = ObtainDispersionFunction(), technique = ObtainFunctionTechnique(), option_fe;
  if (technique == 2) {
    block_size = ObtainBlockSize();
    option_fe = ObtainExplorationFunction();
  }
  DispersionFunction<long>* fd = nullptr;
  DispersionFunction<long>* fd_2 = nullptr;
  ExplorationFunction<long>* fe = nullptr;
  switch (option_fd) {
    case 1 : {
      fd = new fdModule<long>(table_size);
      break;
    } case 2 : {
      fd = new fdSum<long>(table_size);
      break;
    } case 3 : {
      fd = new fdPseudoRandom<long>(table_size);
      break;
    }
  }
  switch (option_fe) {
    case 1 : {
      fe = new feLineal<long>();
      break;
    } case 2 : {
      fe = new feQuadratic<long>();
      break;
    } case 3 : {
      switch (ObtainDispersionFunctionAvalaible(option_fd)) {
        case 1 : {
          fd_2 = new fdModule<long>(table_size);
          fe = new feDDispersion<long>(fd_2);
          break;
        } case 2 : {
          fd_2 = new fdSum<long>(table_size);
          fe = new feDDispersion<long>(fd_2);
          break;
        } case 3 : {
          fd_2 = new fdPseudoRandom<long>(table_size);
          fe = new feDDispersion<long>(fd_2);
          break;
        }
      }
      break;
    } case 4 : {
      fe = new feRedispersion<long>();
      break;
    }
  }
  HashTable<long> table(table_size, fd, fe, block_size);
  while (true) {
    switch (Menu()) {
      case 1 : {
        long element;
        std::cout << "Introduzca un elemento : ";
        std::cin >> element;
        if (table.search(element)) {
          std::cout << GRN "\nElemento encontrado!" NC << std::endl;
        } else {
          std::cout << RED "\nEl elemento no ha podido ser encontrado!" NC << std::endl;
        }
        usleep(2000000);
        break;
      } case 2 : {
        long element;
        std::cout << "Introduzca un elemento : ";
        std::cin >> element;
        if (table.insert(element)) {
          std::cout << GRN "\nElemento insertado con éxito!" NC << std::endl;
        } else {
          std::cout << RED "\nEl elemento no ha podido ser insertado!" NC << std::endl;
        }
        usleep(2000000);
        break;
      } default : {
        break;
      }
    }
  }
  return 0;
}