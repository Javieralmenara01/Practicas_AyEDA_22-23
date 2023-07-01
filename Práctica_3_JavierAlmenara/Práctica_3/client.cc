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
 * @file: client.cc
 *    Programa cliente
 */

#include "bigint.h"
#include "bigintexception.h"
#include "calculator.h"
#include "functions.h"
#include <typeinfo>

/**
 * Function Main
 * @brief Función principal del programa cliente.
 * @param argc : Nos permite obtener el número de argumentos pasados por línea de comandos en la ejecución.
 * @param argv : Nos permite obtener los argumentos pasados por línea de comandos en la ejecución.
 */
int main(int argc, char** argv) {
  std::string name_fin, name_fout;
  try {
    Usage(argc, argv);
  } catch (const std::exception& excp) {
    std::cerr << excp.what() << "Se ha procedido a abortar al programa debido a un error con los ficheros especificados" << std::endl;
    Help();
    return 1;
  }
  std::ifstream input_file{argv[1]};
  std::ofstream output_file{argv[2]};
  std::string line_selected, tag, aux;
  std::map<std::string, Number*> all_numbers;
  int global_base = 10;
  while (getline(input_file, line_selected)) {
    std::stringstream stream_line_aux{line_selected}; 
    stream_line_aux >> tag >> aux;
    try {
      if (aux == "=")  {
        std::string base_str, num;
        stream_line_aux >> base_str >> num;
        int base_esp = RemoveComma(base_str);
        global_base = base_esp;
        Number* number = Number::create(base_esp, num);
        all_numbers.insert(std::pair<std::string, Number*>(tag, number));
      } else if (aux == "?") {
        Calculator calculator {line_selected, all_numbers};
        Number* number = calculator.EvaluateExpression();
        all_numbers.insert(std::pair<std::string, Number*>(tag, number));
      }
    } catch (const char* exception) {
      Number* number = Number::create(global_base, "0");
      all_numbers.insert(std::pair<std::string, Number*>(tag, number));
    } catch (...) {
      std::cerr << "Se ha considerado necesario abortar el programa!" << std::endl
                << "Por favor compruebe el error considerado." << std::endl;
      break;
    }
  }
  auto item = all_numbers.begin();
  while (item != all_numbers.end()) {
    auto scnd = item->second;
    output_file << item->first << " = " << *scnd << std::endl;
    ++item;
  }
  return 0;
}