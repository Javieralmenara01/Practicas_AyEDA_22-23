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
 * @file: functions.cc
 *    Definición de funciones utilizadas
 */

#include "functions.h"

/**
 * @brief Función para iniciar el programa y mostrar una barra de progreso
 */
void StartProgram() {
  system("clear");
  std::string charge, uncharge = "............................................................";
  std::cout << GRN "##############   Práctica 6: Implementación del TDA Árbol  ###############\n\n";
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
 * Función para obtener el tipo de árbol a utilizar en el programa
 */
unsigned ObtainTree() {
  int algorithm_num = -1;
  system("clear");
  while (algorithm_num < 0) {
    std::cout << "Elija una árbol\n" << std::endl;
    std::cout << "[1] ÁrbolABB\n" << "[2] ÁrbolAVL\n" << "[0] Exit" << std::endl;
    std::cout << "\nIntroduzca el número de la opción : ";
    std::cin >> algorithm_num;
    if (algorithm_num < 0 || algorithm_num > 2) {
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
 * Función para obtener la operación a realizar sobre el árbol seleccionado
 */
unsigned ObtainOption() {
  int algorithm_num = -1;
  system("clear");
  while (algorithm_num < 0) {
    std::cout << "Elija una árbol\n" << std::endl;
    std::cout << "[1] Insertar clave\n" << "[2] Buscar clave\n" << "[3] Mostrar árbol inorden\n" << "[0] Exit" << std::endl;
    std::cout << "\nIntroduzca el número de la opción : ";
    std::cin >> algorithm_num;
    if (algorithm_num < 0 || algorithm_num > 3) {
      std::cout << RED "\nSeleccione una opción correcta!\n" NC << BLCK "[0] Para salir del programa!" NC << std::endl;
      algorithm_num = -1;
      usleep(2000000);
    }
    system("clear");
  }
  return (unsigned)algorithm_num;
}
