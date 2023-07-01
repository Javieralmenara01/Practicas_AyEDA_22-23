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
 *    La clase number nos permite operar y representar números enteros.
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

/// Uso de template method pattern
template <size_t Base>
class BigInt;

class Number {
 public:
  /// Operaciones aritméticas
  virtual Number* add(const Number*) const = 0; 
  virtual Number* subtract(const Number*) const = 0; 
  virtual Number* multiply(const Number*) const = 0; 
  virtual Number* divide(const Number*) const = 0; 
  virtual Number* modulo(const Number*) const = 0; 
  virtual Number* power(const Number*) const = 0; 
  /// Operadores de conversión de tipo 
  virtual operator BigInt<2>() const = 0; 
  virtual operator BigInt<8>() const = 0; 
  virtual operator BigInt<10>() const = 0; 
  virtual operator BigInt<16>() const = 0;
  /// Operadores de inserción y extracción de flujo
  // virtual std::ostream& write(std::ostream&) const = 0;
  // virtual std::istream& read(std::istream&) = 0;
  friend std::ostream& operator<<(std::ostream&, const Number&); 
  // friend std::istream& operator>>(std::istream&, Number&);
  /// Creación de los objetos en memoria dinámica
  // static Number* create(size_t base, const std::string& s);
};