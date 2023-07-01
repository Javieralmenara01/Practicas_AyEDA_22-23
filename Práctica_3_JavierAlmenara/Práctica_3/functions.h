/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 3: Calculadora universal para números enteros grandes
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 01/03/2023
 * @file: functions.h
 *    Declaración de funciones.
 */

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

void Usage(int, char**);
void Help();
int GetBase(const std::string&);
int RemoveComma(const std::string&);
std::string ReturnValue(const char*);