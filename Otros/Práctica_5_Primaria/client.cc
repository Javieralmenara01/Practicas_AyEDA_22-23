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

int main(int argc, char** argv) {
  StartProgram();
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
      method = new Insertion<long>(sequence, sequence_size);
      break;
    } case 2: {
      method = new MergeSort<long>(sequence, sequence_size);
      break;
    } case 3: {
      method = new ShellSort<long>(sequence, sequence_size, alpha);
      break;
    } case 4: {
      method = new HeapSort<long>(sequence, sequence_size);
      break;
    } case 5: {
      method = new RadixSort<long>(sequence, sequence_size);
      break;
    }
  }
  method->Print();
  method->Sort();
  method->Print();
  return 0;
}