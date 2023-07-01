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

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"
#define BLCK "\033[1m"

void StartProgram();
unsigned Menu();
size_t ObtainTableSize();
unsigned ObtainDispersionFunction();
unsigned ObtainFunctionTechnique();
size_t ObtainBlockSize();
unsigned ObtainExplorationFunction();
unsigned ObtainDispersionFunctionAvalaible(const unsigned);
unsigned StringToUnsigned(const std::string& s);
bool EsUnaMatricula(const std::string& s);