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
 *    La clase racional nos permite operar y representar números racionales.
 */

#include "bigintexception.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <map>
#include "number.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#pragma once

/// Uso de template method pattern
template <size_t Base>
class BigInt;

/**
 * Clase Racional
 * @brief Permite la representación de números grandes
 */
class Racional : public Number {
 public:
  /// Constructores
  Racional(long n = 0, long d = 1);
  Racional(const Racional&); /// Constructor de copia
  /// Creación de los objetos en memoria dinámica
  static Number* create(size_t base, const std::string& s);
  /// Operadores de conversión de tipo 
  operator BigInt<2>() const override; 
  operator BigInt<8>() const override; 
  operator BigInt<10>() const override; 
  operator BigInt<16>() const override; 
  /// Asignación
  Racional& operator=(const Racional&);
  /// Inserción y extracción en flujo
  friend std::ostream& operator<<(std::ostream&, const Racional&); 
  friend std::istream& operator>>(std::istream&, Racional&);
  /// Operadores de inserción y extracción de flujo
  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&) override;
  /// Getters
  /// Operaciones aritméticas racional
  friend Racional operator*(const Racional&, const Racional&); 
  friend Racional operator/(const Racional&, const Racional&); 
  /// Operaciones aritméticas Number
  Number* add(const Number*) const override; 
  Number* subtract(const Number*) const override; 
  Number* multiply(const Number*) const override; 
  Number* divide(const Number*) const override; 
  Number* module(const Number*) const override; 
  Number* power(const Number*) const override; 
 private:
  long num_ = 0;
  long den_ = 1;
};

