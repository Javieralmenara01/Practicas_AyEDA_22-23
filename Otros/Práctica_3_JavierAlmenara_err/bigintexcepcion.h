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
 * @file: number.h
 *    La clase BigIntException nos permite gestionar las excepciones producidas durante la ejecución del programa cliente.
 */

#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class BigIntExcepcion : public std::exception {
 public: 
  const char* BigIntBadDigit() const throw() {
    return "An error has been detected, the specified data type does not belong to the object.";
  }
  const char* BigIntDivisionByZero() const throw() {
    return "Cannot be divided by zero!";
  }
  const char* BigIntBaseNotImplemented() const throw() {
    return "The introduced base has not been implemented!";
  }
  const char* what() const throw() {
    return "BigInt Exception";
  }
};