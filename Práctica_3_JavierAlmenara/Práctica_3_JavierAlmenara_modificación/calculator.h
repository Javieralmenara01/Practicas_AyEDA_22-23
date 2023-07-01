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
 * @file: calculator.h
 *    La clase Calculator nos permite operar con número de la clase BigInt.
 */

#pragma once

#include "bigint.h"
#include "bigintexception.h"
#include <iostream>
#include <fstream>
#include <set>
#include <stack>
#include <string>
#include <sstream>

/**
 * Enumeración de Opciones
 * @brief Enumeración de opciones, orientados a usarla en la clase Calculadora.
 */
enum Options {
  SUMA,
  RESTA,
  MULTIPLICACION,
  DIVISION,
  MODULO,
  POTENCIA,
  OTHER,
};

/**
 * Clase Calculadora Polaca de Notación Inversa
 * @brief Calculadora Polaca Inversa que nos permite, la implementación de cierto tipos de expresiones.
 */
class Calculator {
 public:
  // Constructor
  Calculator(const std::string& line_to_read, const std::map<std::string, Number*> numbers) : line_to_read_{line_to_read}, numbers_{numbers} {}
  // Getters
  std::string line_to_read() const { return line_to_read_; }
  std::map<std::string, Number*> numbers() const { return numbers_; }
  // Cálculo
  Number* EvaluateExpression() const;
 private:
  std::string line_to_read_;
  std::map<std::string, Number*> numbers_;
};

/**
 * Resolve Option
 * @brief: Método auxiliar para resolver la estructura switch.
 * @param input: Cadena de entrada
 */
Options resolve_option(const std::string& input) {
  if (input == "+") return SUMA;
  if (input == "-") return RESTA;
  if (input == "*") return MULTIPLICACION;
  if (input == "/") return DIVISION;
  if (input == "%") return MODULO;
  if (input == "^") return POTENCIA;
  return OTHER;
}

/**
 * Método Evaluate Expression
 * @brief Nos permite evaluar una expresión en notación polaca inversa, para objetos Number*.
 */
Number* Calculator::EvaluateExpression() const {
  std::string line_read = line_to_read(), aux, before_aux;
  std::map<std::string, Number*> all_numbers = numbers();
  std::stack<Number*> stack_numbers;
  std::stringstream stream_line {line_read}; stream_line >> aux >> aux;
  while (stream_line.good()) {
    stream_line >> aux;
    if (aux == before_aux) {
      break;
    }
    switch (resolve_option(aux)) {
      case SUMA: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        Number* number_2 = stack_numbers.top();
        stack_numbers.pop();
        Number* number_1 = stack_numbers.top();
        stack_numbers.pop();
        stack_numbers.push(number_1->add(number_2));
        break;
      } case RESTA: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        Number* number_2 = stack_numbers.top();
        stack_numbers.pop();
        Number* number_1 = stack_numbers.top();
        stack_numbers.pop();
        stack_numbers.push(number_1->subtract(number_2));
        break;
      } case MULTIPLICACION: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        Number* number_2 = stack_numbers.top();
        stack_numbers.pop();
        Number* number_1 = stack_numbers.top();
        stack_numbers.pop();
        stack_numbers.push(number_1->multiply(number_2));
        break;
      } case DIVISION: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        Number* number_2 = stack_numbers.top();
        stack_numbers.pop();
        Number* number_1 = stack_numbers.top();
        stack_numbers.pop();
        stack_numbers.push(number_1->divide(number_2));
        break;
      } case MODULO: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        Number* number_2 = stack_numbers.top();
        stack_numbers.pop();
        Number* number_1 = stack_numbers.top();
        stack_numbers.pop();
        stack_numbers.push(number_1->module(number_2));
        break;
      } case POTENCIA: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        Number* number_2 = stack_numbers.top();
        stack_numbers.pop();
        Number* number_1 = stack_numbers.top();
        stack_numbers.pop();
        stack_numbers.push(number_1->power(number_2));
        break;        
      } default: {
        auto item = all_numbers.find(aux);
        if (item == all_numbers.end()) {
          throw std::invalid_argument("Etiqueta no encontrada!");
        }
        stack_numbers.push(item->second);
      }
    }
    before_aux = aux;
  }
  Number* number_result;
  if (stack_numbers.size() == 1) {
    number_result = stack_numbers.top();
  } else {
    throw std::invalid_argument("Expresión Incorrecta!");
  }
  return number_result;
}