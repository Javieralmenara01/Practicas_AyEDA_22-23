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
 * @file: sequence.h
 *    Clase que permite definir un tipo de dato abstracto denominado sequence
 */

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <iomanip>
#include <functional>
#include <string>
#include <unordered_set>
#include "functions.h"

/**
 * Clase Vehículo
 */
class Vehiculo {
 public:
  Vehiculo();
  Vehiculo(const std::string);
  void operator=(const Vehiculo&);
  void operator=(const int);
  friend bool operator==(const Vehiculo&, const Vehiculo&);
  operator long() const;
  operator int() const;
  operator unsigned() const;
  friend std::istream& operator>>(std::istream&, Vehiculo&);
  friend std::ostream& operator<<(std::ostream&, const Vehiculo&);
 private:
  std::string matricula_;
};