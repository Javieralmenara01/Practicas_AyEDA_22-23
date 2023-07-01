/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 2: Representación de números grandes en notación posicional
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 06/02/2023
 * @file: calculator.h
 *    La clase Calculator nos permite operar con número de la clase BigInt.
 */

#pragma once

#include "bigint.h"
#include <iostream>
#include <fstream>
#include <set>
#include <stack>
#include <string>
#include <sstream>

#pragma once

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
 * Calculadora Polaca de Notación Inversa
 */
template<size_t Base>
class Calculator {
 public:
  // Constructor
  Calculator <Base>(const std::string& line_to_read, const std::map<std::string, BigInt<Base>>& numbers) : line_to_read_{line_to_read}, numbers_{numbers} {}
  // Getters
  std::string line_to_read() const { return line_to_read_; }
  std::map<std::string, BigInt<Base>> numbers() const { return numbers_; }
  // Cálculo
  BigInt<Base> EvaluateExpression(bool work_in_base_two);
 private:
  std::string line_to_read_;
  std::map<std::string, BigInt<Base>> numbers_;
};

/**
 * Resolve Option
 * @brief: Método auxiliar para resolver la estructura switch
 * @param input: Cadena de entrada
 */
Options resolve_option(std::string input) {
  if (input == "+") return SUMA;
  if (input == "-") return RESTA;
  if (input == "*") return MULTIPLICACION;
  if (input == "/") return DIVISION;
  if (input == "%") return MODULO;
  if (input == "^") return POTENCIA;
  return OTHER;
}

/**
 * Método EvaluateExpression
 * @brief Permite elvaluar una expresión, expresada en notación polaca inversa
 * @param work_in_base_two : Trabajar con base 2
 */
template<size_t Base>
BigInt<Base> Calculator<Base>::EvaluateExpression(bool work_in_base_two) {
  std::string line_read = line_to_read(), aux, before_aux;
  std::map<std::string, BigInt<Base>> all_numbers = numbers();
  std::stack<BigInt<Base>> stack_numbers;
  std::stringstream stream_line {line_read};
  stream_line >> aux >> aux;
  while (stream_line.good()) {
    stream_line >> aux;
    if (before_aux == aux && stream_line.str()[stream_line.str().size() - 1] == ' ') {
      std::cerr << "El final del fichero de entrada, contiene espacios en blanco !" << std::endl;
      break;
    }
    switch (resolve_option(aux)) {
      case SUMA: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
          exit(EXIT_SUCCESS);
        }
        BigInt<Base> number_2 = stack_numbers.top();
        stack_numbers.pop();
        BigInt<Base> number_1 = stack_numbers.top();
        stack_numbers.pop();
        if (work_in_base_two) {
          stack_numbers.push(static_cast<BigInt<Base>>(static_cast<BigInt<2>>(number_1) + static_cast<BigInt<2>>(number_2)));
        } else {
          stack_numbers.push(number_1 + number_2);
        }
        break;
      } case RESTA: {
        if (stack_numbers.size() < 2) {
          BigInt<Base> number_1 = stack_numbers.top();
          stack_numbers.pop();
          stack_numbers.push(-number_1);
        }
        BigInt<Base> number_2 = stack_numbers.top();
        stack_numbers.pop();
        BigInt<Base> number_1 = stack_numbers.top();
        stack_numbers.pop();
        if (work_in_base_two) {
          stack_numbers.push(static_cast<BigInt<Base>>(static_cast<BigInt<2>>(number_1) - static_cast<BigInt<2>>(number_2)));
        } else {
          stack_numbers.push(number_1 - number_2);
        }
        break;
      } case MULTIPLICACION: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        BigInt<Base> number_2 = stack_numbers.top();
        stack_numbers.pop();
        BigInt<Base> number_1 = stack_numbers.top();
        stack_numbers.pop();
        if (work_in_base_two) {
          stack_numbers.push(static_cast<BigInt<Base>>(static_cast<BigInt<2>>(number_1) * static_cast<BigInt<2>>(number_2)));
        } else {
          stack_numbers.push(number_1 * number_2);
        }
        break;
      } case DIVISION: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        BigInt<Base> number_2 = stack_numbers.top();
        stack_numbers.pop();
        BigInt<Base> number_1 = stack_numbers.top();
        stack_numbers.pop();
        if (work_in_base_two) {
          stack_numbers.push(static_cast<BigInt<Base>>(static_cast<BigInt<2>>(number_1) / static_cast<BigInt<2>>(number_2)));
        } else {
          stack_numbers.push(number_1 / number_2);
        }
        break;
      } case MODULO: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        BigInt<Base> number_2 = stack_numbers.top();
        stack_numbers.pop();
        BigInt<Base> number_1 = stack_numbers.top();
        stack_numbers.pop();
        if (work_in_base_two) {
          stack_numbers.push(static_cast<BigInt<Base>>(static_cast<BigInt<2>>(number_1) % static_cast<BigInt<2>>(number_2)));
        } else {
          stack_numbers.push(number_1 % number_2);
        }
        break;
      } case POTENCIA: {
        if (stack_numbers.size() < 2) {
          throw std::invalid_argument("Error! Número de objetos de la clase BigInt almacenados insuficientes!");
        }
        BigInt<Base> number_2 = stack_numbers.top();
        stack_numbers.pop();
        BigInt<Base> number_1 = stack_numbers.top();
        stack_numbers.pop();
        if (work_in_base_two) {
          stack_numbers.push(static_cast<BigInt<Base>>(power(static_cast<BigInt<2>>(number_1), static_cast<BigInt<2>>(number_2))));
        } else {
          stack_numbers.push(power(number_1, number_2));
        }
        break;        
      } default: {
        if (aux.size() >= 3) {
          if ((aux[0] == '+' && aux[1] == '+') || (aux[0] == '-' && aux[1] == '-')) {
            aux.erase(0, 2);
            auto item = all_numbers.find(aux);
            if (item == all_numbers.end()) {
              throw std::invalid_argument("Etiqueta no encontrada!");
            }
            BigInt<Base> number_1 = item->second;
            if ((aux[0] == '+' && aux[1] == '+')) {
              ++number_1;
              stack_numbers.push(number_1);
            } else {
              --number_1;
              stack_numbers.push(number_1);
            }
            break;
          } else if (((aux[aux.size() - 2] == '+' && aux[aux.size() - 1] == '+') || (aux[aux.size() - 2] == '-' && aux[aux.size() - 1] == '-'))) {
            aux.erase(aux.size() - 2, 2);
            auto item = all_numbers.find(aux);
            if (item == all_numbers.end()) {
              throw std::invalid_argument("Etiqueta no encontrada!");
            }
            BigInt<Base> number_1 = item->second;
            if ((aux[0] == '+' && aux[1] == '+')) {
              stack_numbers.push(number_1++);
            } else {
              stack_numbers.push(number_1--);
            }
            break;
          }
        }
        auto item = all_numbers.find(aux);
        if (item == all_numbers.end()) {
          throw std::invalid_argument("Etiqueta no encontrada!");
        }
        stack_numbers.push(item->second);
      }
    }
    before_aux = aux;
  }
  BigInt<Base> number_result;
  if (stack_numbers.size() == 1) {
    number_result = stack_numbers.top();
  } else {
    throw std::invalid_argument("Expresión Incorrecta!");
  }
  return number_result;
}