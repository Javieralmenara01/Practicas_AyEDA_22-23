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
 * @file: functions.cc
 *    Definicion de las funciones usadas en el programa
 */

#include "functions.h"

/**
 * Función de Inicio de Programa
 */
void StartProgram() {
  system("clear");
  std::string charge, uncharge = "............................................................";
  std::cout << GRN "##############   Práctica 4: Búsqueda por dispersión   ###############\n\n";
  std::cout << GRN "Iniciando programa...\n\n";
  /// Barra de progreso
  for (int i = 0; i <= 100; i += 10) {
    std::cout << "[" << charge << uncharge << "]  [" << i << "%]";
    fflush(stdout);
    usleep(100000);
    charge += "######";
    if (uncharge.size() > 6) {
      uncharge.erase(uncharge.begin(), uncharge.begin() + 6);
    } else {
      uncharge = "";
    }
    std::cout << "\r";
  }
  /// Limpieza de la consola
  system("clear");
  std::cout << "Programa iniciado correctamente.\n" NC;
}

/**
 * Función para obtener el algoritmo a utilizar
 */
unsigned ObtainAlgorithm() {
  int algorithm_num = -1;
  system("clear");
  while (algorithm_num < 0) {
    std::cout << "Elija una algoritmo\n" << std::endl;
    std::cout << "[1] Inserción\n" << "[2] MergeSort\n" << "[3] ShellSort\n" << "[4] HeapSort\n" << "[5] RadixSort\n" << "[6] QuickSort\n" << "[0] Exit" << std::endl;
    std::cout << "\nIntroduzca el número de la opción : ";
    std::cin >> algorithm_num;
    if (algorithm_num < 0 || algorithm_num > 6) {
      std::cout << RED "\nSeleccione una opción correcta!\n" NC << BLCK "[0] Para salir del programa!" NC << std::endl;
      algorithm_num = -1;
      usleep(2000000);
    }
    system("clear");
  }
  if (algorithm_num == 0) {
    exit(1);
  }
  return (unsigned)algorithm_num;
}

/**
 * Función para obtener el tamaño de la secuencia
 */
unsigned ObtainSize() {
  int size = -1;
  system("clear");
  while (size < 0) {
    std::cout << "Introduzca el tamaño de la secuencia : ";
    std::cin >> size;
    if (size < 0) {
      std::cout << RED "\nSeleccione una opción correcta!\n" NC << BLCK "[0] Para salir del programa!" NC << std::endl;
      usleep(2000000);
    }
    system("clear");
  }
  if (size == 0) {
    exit(1);
  }
  return (unsigned)size;
}

/**
 * Función para obtener el valor de alpha
 */
double ObtainAlpha() {
  double alpha = -1;
  system("clear");
  while (alpha < 0) {
    std::cout << "Introduzca el valor de alpha : ";
    std::cin >> alpha;
    if (alpha <= 0 || alpha >= 1) {
      std::cout << RED "\nSeleccione una opción correcta!\n" << NC << BLCK "Recuerde [0 < alpha < 1]\n" NC << std::endl;
      alpha = -1.0;
      usleep(2000000);
    }
    system("clear");
  }
  return alpha;
}

/**
 * Función obtener la condición para generar números random
 */
bool ObtainConditionRandom() {
  int condition = -1;
  system("clear");
  while (condition < 0) {
    std::cout << "¿Desea introducir los números de forma manual(0) o de forma aleatoria(1)? : ";
    std::cin >> condition;
    if (condition < 0 || condition > 1) {
      std::cout << RED "\nSeleccione una opción correcta!\n" << NC << BLCK "Recuerde [0 < alpha < 1]\n" NC << std::endl;
      condition = -1;
      usleep(2000000);
    }
    system("clear");
  }
  return (bool)condition;
}

/**
 * Función obtener la condición para generar números random
 */
bool RepeatProgram() {
  int condition = -1;
  while (condition < 0) {
    std::cout << "\n ¿Desea volver a ejecutar el programa? No(0) o Sí(1) : ";
    std::cin >> condition;
    if (condition < 0 || condition > 1) {
      std::cout << RED "\nSeleccione una opción correcta!\n" NC << std::endl;
      condition = -1;
      usleep(2000000);
    }
    system("clear");
  }
  return (bool)condition;
}