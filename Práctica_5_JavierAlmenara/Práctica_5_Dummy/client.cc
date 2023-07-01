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
#include "contador.h"
#include "functions.h"
#include "heapsort.h"
#include "insertion.h"
#include "mergesort.h"
#include "quicksort.h"
#include "radixsort.h"
#include "shellsort.h"
#include "vehiculo.h"

int Contador::cuenta = 0;

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
    std::vector<Vehiculo> sequence(sequence_size); 
    if (random_numbers) {
      sequence = GenerateRandomNumbers<Vehiculo>(sequence_size);
    } else {
      sequence = EnterSequenceNumbers<Vehiculo>(sequence_size);
    }
    SortMethod<Vehiculo>* method;
    switch (algorithm_num) {
      case 1: {
        if (random_numbers) {
          method = new Insertion<Vehiculo, false>(sequence, sequence_size);
        } else {
          method = new Insertion<Vehiculo, true>(sequence, sequence_size);
        }
        break;
      } case 2: {
        if (random_numbers) {
          method = new MergeSort<Vehiculo, false>(sequence, sequence_size);
        } else {
          method = new MergeSort<Vehiculo, true>(sequence, sequence_size);
        }
        break;
      } case 3: {
        if (random_numbers) {
          method = new ShellSort<Vehiculo, false>(sequence, sequence_size, alpha);
        } else {
          method = new ShellSort<Vehiculo, true>(sequence, sequence_size, alpha);
        }
        break;
      } case 4: {
        if (random_numbers) {
          method = new HeapSort<Vehiculo, false>(sequence, sequence_size);
        } else {
          method = new HeapSort<Vehiculo, true>(sequence, sequence_size);
        }
        break;
      } case 5: {
        if (random_numbers) {
          method = new RadixSort<Vehiculo, false>(sequence, sequence_size);
        } else {
          method = new RadixSort<Vehiculo, true>(sequence, sequence_size);
        }
        break;
      } case 6: {
        if (random_numbers) {
          method = new QuickSort<Vehiculo, false>(sequence, sequence_size);
        } else {
          method = new QuickSort<Vehiculo, true>(sequence, sequence_size);
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
    std::cout << "\nNúmero de veces que intercambiado elementos = " << Contador::Valor() << std::endl;
    Contador::Resetear();
    usleep(3000000);
  }
  return 0;
}