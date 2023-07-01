/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 1: Representación de números grandes en notación posicional
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 06/02/2023
 * @file: client.cc
 *    Archivo cliente.
 */

#include "bigint.h"
#include "calculator.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include "functions.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
  std::cout << catalan<10>(8) << std::endl;
  Usage(argc, argv);
  std::ifstream file{argv[1]};
  std::ofstream file_out {argv[2]};
  std::string line_selected, tag, aux;
  int base{0};
  getline(file, line_selected);
  std::stringstream stream_line{line_selected};
  stream_line >> aux >> aux >> aux;
  base = stoi(aux);
  switch (base) {
    case 2: {
      std::map<std::string, BigInt<2>> all_numbers;
      while (getline(file, line_selected)) {
        std::stringstream stream_line_aux{line_selected};
        stream_line_aux >> tag;
        auto item = all_numbers.find(aux);
        stream_line_aux >> aux >> aux;
        if (item == all_numbers.end() && isdigit(aux[0]))  {
          BigInt<2> number{aux};
          all_numbers.insert(std::pair<std::string, BigInt<2>>(tag, number));
        } else {
          Calculator<2> calculator {line_selected, all_numbers};
          BigInt<2> number = calculator.EvaluateExpression();
          all_numbers.insert(std::pair<std::string, BigInt<2>>(tag, number));
        }
      }
      file_out << "Base = " << base << std::endl;
      auto item = all_numbers.begin();
      while (item != all_numbers.end()) {
        file_out << item->first << " = " << item->second << std::endl;
        ++item;
      }
      break;
    } case 8: {
      std::map<std::string, BigInt<8>> all_numbers;
      while (getline(file, line_selected)) {
        std::stringstream stream_line_aux{line_selected};
        stream_line_aux >> tag;
        auto item = all_numbers.find(aux);
        stream_line_aux >> aux >> aux;
        if (item == all_numbers.end() && isdigit(aux[0]))  {
          BigInt<8> number{aux};
          all_numbers.insert(std::pair<std::string, BigInt<8>>(tag, number));
        } else {
          Calculator<8> calculator {line_selected, all_numbers};
          BigInt<8> number = calculator.EvaluateExpression();
          all_numbers.insert(std::pair<std::string, BigInt<8>>(tag, number));
        }
      }
      file_out << "Base = " << base << std::endl;
      auto item = all_numbers.begin();
      while (item != all_numbers.end()) {
        file_out << item->first << " = " << item->second << std::endl;
        ++item;
      }
      break;
    } case 10: {
      std::map<std::string, BigInt<10>> all_numbers;
      while (getline(file, line_selected)) {
        std::stringstream stream_line_aux{line_selected};
        stream_line_aux >> tag;
        auto item = all_numbers.find(tag);
        stream_line_aux >> aux >> aux;
        if (item == all_numbers.end() && isdigit(aux[0])) {
          BigInt<10> number{aux};
          all_numbers.insert(std::pair<std::string, BigInt<10>>(tag, number));
        } else {
          Calculator<10> calculator {line_selected, all_numbers};
          BigInt<10> number = calculator.EvaluateExpression();
          all_numbers.insert(std::pair<std::string, BigInt<10>>(tag, number));
        }
      }
      file_out << "Base = " << base << std::endl;
      auto item = all_numbers.begin();
      while (item != all_numbers.end()) {
        file_out << item->first << " = " << item->second << std::endl;
        ++item;
      }
      break;
    } case 16: {
      std::map<std::string, BigInt<16>> all_numbers;
      while (getline(file, line_selected)) {
        std::stringstream stream_line_aux{line_selected};
        stream_line_aux >> tag;
        auto item = all_numbers.find(tag);
        stream_line_aux >> aux >> aux;
        bool condition = true;
        for (int i = 0; i < (int)aux.size(); i++) {
          if (!(isdigit(aux[0]) || (aux[0] >= 'A' && aux[0] <= 'F'))) {
            condition = false;
          }
        }
        if (item == all_numbers.end() && condition)  {
          BigInt<16> number{aux};
          all_numbers.insert(std::pair<std::string, BigInt<16>>(tag, number));
        } else {
          Calculator<16> calculator {line_selected, all_numbers};
          BigInt<16> number = calculator.EvaluateExpression();
          all_numbers.insert(std::pair<std::string, BigInt<16>>(tag, number));
        }
      }
      file_out << "Base = " << base << std::endl;
      auto item = all_numbers.begin();
      while (item != all_numbers.end()) {
        file_out << item->first << " = " << item->second << std::endl;
        ++item;
      }
      break;
    } default: {
      throw std::invalid_argument("Base especificada inválida!");
    }
  }

  return 0;
}