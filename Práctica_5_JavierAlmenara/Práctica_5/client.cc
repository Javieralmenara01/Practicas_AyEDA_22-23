/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 5: Ordenación
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 06/04/2023
 * @file: client.cc
 *    Fichero cliente que efectua la interacción con el usuario.
 */

#include <iostream>
#include "functions.h"
#include "insertion.h"
#include "mergesort.h"
#include "shellsort.h"
#include "heapsort.h"
#include "radixsort.h"
#include "quicksort.h"

int main(int argc, char** argv) {
  StartProgram();
  bool program_on = true;
  while (program_on) {
    unsigned algorithm_num = ObtainAlgorithm(), sequence_size = ObtainSize();
    double alpha = 0;
    if (algorithm_num == 3) {
      alpha = ObtainAlpha();
    }
    bool random_numbers = ObtainConditionRandom();
    std::vector<long> sequence(sequence_size); 
    if (random_numbers) {
      sequence = GenerateRandomNumbers<long>(sequence_size);
    } else {
      sequence = EnterSequenceNumbers<long>(sequence_size);
    }
    SortMethod<long>* method;
    switch (algorithm_num) {
      case 1: {
        if (random_numbers) {
          method = new Insertion<long, false>(sequence, sequence_size);
        } else {
          method = new Insertion<long, true>(sequence, sequence_size);
        }
        break;
      } case 2: {
        if (random_numbers) {
          method = new MergeSort<long, false>(sequence, sequence_size);
        } else {
          method = new MergeSort<long, true>(sequence, sequence_size);
        }
        break;
      } case 3: {
        if (random_numbers) {
          method = new ShellSort<long, false>(sequence, sequence_size, alpha);
        } else {
          method = new ShellSort<long, true>(sequence, sequence_size, alpha);
        }
        break;
      } case 4: {
        if (random_numbers) {
          method = new HeapSort<long, false>(sequence, sequence_size);
        } else {
          method = new HeapSort<long, true>(sequence, sequence_size);
        }
        break;
      } case 5: {
        if (random_numbers) {
          method = new RadixSort<long, false>(sequence, sequence_size);
        } else {
          method = new RadixSort<long, true>(sequence, sequence_size);
        }
        break;
      } case 6: {
        if (random_numbers) {
          method = new QuickSort<long, false>(sequence, sequence_size);
        } else {
          method = new QuickSort<long, true>(sequence, sequence_size);
        }
        break;
      }
    }
    if (random_numbers) {
      method->Print();
    }
    method->Sort();
    method->Print();
    program_on = RepeatProgram();
  }
  return 0;
}