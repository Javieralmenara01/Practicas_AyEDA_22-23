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
 * @file: functions.cc
 *    Fichero que almacena las funciones que guarda el usuario
 */

#include "functions.h"

/**
 * Función de Inicio de Programa
 */
void StartProgram() {
  system("clear");
  std::string charge, uncharge = "............................................................";
  std::cout << GRN "##############   Práctica 4: Búsqueda por dispersión   ###############\n\n";
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
 * Función de Menu
 */
unsigned Menu() {
  system("clear");
  int option = -1;
  while (option < 0 || option > 2) {
    std::cout << "##############   Menu   ###############\n\n"
    << "Opciones :\n" << "[1] Buscar elemento\n" << "[2] Insertar elemento\n"
    << "[0] Exit\n" << "\nIntroduzca el número de la opción : ";
    std::cin >> option;
    if (option < 0 || option > 3) {
      std::cout << RED "Seleccione una opción correcta!" NC << std::endl;
      usleep(1000000);
    }
    system("clear");
  }
  if (option == 0) {
    exit(0);
  }
  unsigned option_u = (unsigned)option;
  return option_u;
}

/**
 * Función para obtener el tamaño de la tabla
 */
size_t ObtainTableSize() {
  int table_size = -1;
  system("clear");
  while (table_size < 0) {
    std::cout << "Introduzca el tamaño de la tabla : ";
    std::cin >> table_size;
    if (table_size < 0) {
      std::cout << RED "\nSeleccione una opción correcta!\n" NC << BLCK "[0] Para salir del programa!" NC << std::endl;
      usleep(2000000);
    }
    system("clear");
  }
  if (table_size == 0) {
    exit(1);
  }
  return (size_t)table_size;
}

/**
 * Función para obtener la función de dispersión
 */
unsigned ObtainDispersionFunction() {
  int option = -1;
  while (option < 0 || option > 3) {
    std::cout << "Elija una función de dispersión\n" << std::endl;
    std::cout << "[1] Módulo\n" << "[2] Basada en la suma\n" << "[3] Pseudoaleatoria\n" << "[0] Exit" << std::endl;
    std::cout << "\nIntroduzca el número de la opción : ";
    std::cin >> option;
    if (option < 0 || option > 3) {
      std::cout << RED "Seleccione una opción correcta!" NC << std::endl;
      usleep(1000000);
    }
    system("clear");
  }
  if (option == 0) {
    exit(0);
  }
  unsigned option_u = (unsigned)option;
  return option_u;
}

/**
 * Función para obtener la función de técnica
 */
unsigned ObtainFunctionTechnique() {
  int option = -1;
  while (option < 0 || option > 2) {
    std::cout << "Elija una técina de dispersión\n" << std::endl;
    std::cout << "[1] Dispersión abierta\n" << "[2] Dispersión cerrada\n" << "[0] Exit" << std::endl;
    std::cout << "\nIntroduzca el número de la opción : ";
    std::cin >> option;
    if (option < 0 || option > 2) {
      std::cout << RED "Seleccione una opción correcta!" NC << std::endl;
      usleep(1000000);
    }
    system("clear");
  }
  if (option == 0) {
    exit(1);
  }
  unsigned option_u = (unsigned)option;
  return option_u;
}

/**
 * Función para obtener el bloque de la clase Block
 */
size_t ObtainBlockSize() {
  int block_size = -1;
  system("clear");
  while (block_size < 0) {
    std::cout << "Introduzca el tamaño del bloque : ";
    std::cin >> block_size;
    if (block_size < 0) {
      std::cout << RED "\nSeleccione una opción correcta!\n" NC << BLCK "[0] Para salir del programa!" NC << std::endl;
      usleep(2000000);
    }
    system("clear");
  }
  if (block_size == 0) {
    exit(1);
  }
  return (size_t)block_size;
}

/**
 * Función para obtener la función de exploracióm
 */
unsigned ObtainExplorationFunction() {
  int option = -1;
  while (option < 0 || option > 4) {
    std::cout << "Elija una función de exploración\n" << std::endl;
    std::cout << "[1] Exploración Lineal\n" << "[2] Exploración Cuadrática\n" << "[3] Doble Dispersión\n"
              << "[4] Redispersión\n" << "[0] Exit" << std::endl;
    std::cout << "\nIntroduzca el número de la opción : ";
    std::cin >> option;
    if (option < 0 || option > 4) {
      std::cout << RED "Seleccione una opción correcta!" NC << std::endl;
      usleep(1000000);
    }
    system("clear");
  }
  if (option == 0) {
    exit(1);
  }
  unsigned option_u = (unsigned)option;
  return option_u;
}

/**
 * Función para obtener la función de dispersión disponible
 */
unsigned ObtainDispersionFunctionAvalaible(const unsigned option_selected) {
  int option = -1;
  while (option < 0 || option > 3) {
    std::cout << "Elija una función de dispersión\n" << std::endl;
    std::cout << "[1] Módulo\n" << "[2] Basada en la suma\n" << "[3] Pseudoaleatoria\n" << "[0] Exit" << std::endl;
    std::cout << "\nIntroduzca el número de la opción : ";
    std::cin >> option;
    if (option < 0 || option > 3) {
      std::cout << RED "Seleccione una opción correcta!" NC << std::endl;
      usleep(1000000);
    }
    if (option == option_selected) {
      option = -1;
      std::cout << RED "Esa función de dispersión ya ha sido escogida, por favor seleccione otra!" NC << std::endl;
      usleep(1000000);
    }
    system("clear");
  }
  if (option == 0) {
    exit(0);
  }
  unsigned option_u = (unsigned)option;
  return option_u;
}

/**
 * Función para obtener un entero a partir de una string
 */
unsigned StringToUnsigned(const std::string& s) {
  unsigned num = 0, base = 1;
  for (auto c : s) {
    if (c >= 'A' && c <= 'Z') {
      num += ((c - 'A') * base);
    } else if (c >= 'a' && c <= 'z') {
      num += ((c - 'a') * base);
    } else if (isdigit(c)) {
      num += (c * base);
    } else {
      std::cerr << "Ha ocurrido un error!" << std::endl;
      exit(0);
    }
    base *= 10;
  }
  std::cout << num << std::endl;
  usleep(300000);
  return num;
}

/**
 * Función para comprobar si la cadena introducida se trataba de una matrícula
 */
bool EsUnaMatricula(const std::string& s) {
  for (auto c : s) {
    if ((!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')) && !isdigit(c)) {
      return false;
    }
  }
  return true;
}