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

#include <chrono>
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
    unsigned sequence_size = 100000;
    double alpha = 0.66;
    std::vector<long> sequence(sequence_size), aux;
    sequence = GenerateRandomNumbers<long>(sequence_size);
    SortMethod<long>* method;
    aux = sequence;
    /// Insertion 
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    sequence = aux;
    method = new Insertion<long, false>(sequence, sequence_size);
    method->Sort();
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;
    std::cout << "El tiempo para Insertion ha sido de : " << elapsedTime.count() << std::endl;
    /// MergeSort
    sequence = aux;
    method = new MergeSort<long, false>(sequence, sequence_size);
    startTime = std::chrono::high_resolution_clock::now();
    method->Sort();
    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = endTime - startTime;
    std::cout << "El tiempo para MergeSort ha sido de : " << elapsedTime.count() << std::endl;
    /// ShellSort
    sequence = aux;
    method = new ShellSort<long, false>(sequence, sequence_size, alpha);
    startTime = std::chrono::high_resolution_clock::now();
    method->Sort();
    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = endTime - startTime;
    std::cout << "El tiempo para ShellSort ha sido de : " << elapsedTime.count() << std::endl;
    /// HeapSort
    sequence = aux;
    method = new HeapSort<long, false>(sequence, sequence_size);
    startTime = std::chrono::high_resolution_clock::now();
    method->Sort();
    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = endTime - startTime;
    std::cout << "El tiempo para HeapSort ha sido de : " << elapsedTime.count() << std::endl;
    /// RadixSort
    sequence = aux;
    method = new RadixSort<long, false>(sequence, sequence_size);
    startTime = std::chrono::high_resolution_clock::now();
    method->Sort();
    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = endTime - startTime;
    std::cout << "El tiempo para RadixSort ha sido de : " << elapsedTime.count() << std::endl;
    /// QuickSort
    sequence = aux;
    method = new QuickSort<long, false>(sequence, sequence_size);
    method->Sort();
    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = endTime - startTime;
    std::cout << "El tiempo para QuickSort ha sido de : " << elapsedTime.count() << std::endl;
    program_on = false;
  }
  return 0;
}