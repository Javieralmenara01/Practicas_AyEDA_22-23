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
  size_t num_total = 1;
  if (block_size != 0) {
    num_total = (block_size * table_size);
  } else {
    num_total = table_size;
  }
  std::vector<long> vect_keys;
  for (int i = 0; i < table_size; i++) {
    long key_to_insert = rand();
    vect_keys.push_back(key_to_insert);
    table.insert(key_to_insert);
    if (i == (num_total / 25)) {
      int total_comp = 0, num_to_check = 10;
      for (int j = 0; j < num_to_check; j++) {
        table.search(vect_keys[rand() % 25]);
        total_comp += table.GetComparisons();
      }
      std::cout << "La media de comparaciones es " << total_comp / 10 << std::endl;
    }
    if (i == (num_total / 50)) {
      int total_comp = 0, num_to_check = 10;
      for (int j = 0; j < num_to_check; j++) {
        table.search(vect_keys[rand() % 50]);
        total_comp += table.GetComparisons();
      }
      std::cout << "La media de comparaciones es " << total_comp / 10 << std::endl;
    }
    if (i == (num_total / 75)) {
      int total_comp = 0, num_to_check = 10;
      for (int j = 0; j < num_to_check; j++) {
        table.search(vect_keys[rand() % 75]);
        total_comp += table.GetComparisons();
      }
      std::cout << "La media de comparaciones es " << total_comp / 10 << std::endl;
    }
  }
  return 0;
}