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
 * @file: racional.h
 *    La clase racional nos permite operar y representar números racionales.
 */

#include "racional.h"
#include "bigint.h"

Racional::Racional(long n, long d) {
  if (d == 0) {
    throw std::invalid_argument("El denominador no puede ser 0");
  }
  num_ = n;
  den_ = d;
}

Racional::Racional(const Racional& n) {
  num_ = n.num_;
  den_ = n.den_;  
}

Racional& Racional::operator=(const Racional& n) {
  num_ = n.num_;
  den_ = n.den_;
  return *this;
}

std::ostream& operator<<(std::ostream& out, const Racional& n) {
  out << n.num_<< "/" << n.den_;
  return out;
}

std::istream& operator>>(std::istream& in, Racional& n) {
  long num, denom;
  in >> num >> denom;
  n.num_ = num;
  if (denom == 0) {
    throw std::invalid_argument("El denominador no puede ser 0");
  }
  n.den_ = denom;
  return in;
}

std::ostream& Racional::write(std::ostream& out) const {
  out << *this;
  return out;
}

std::istream& Racional::read(std::istream& in) {
  in >> *this;
  return in;
}

Racional operator*(const Racional& a, const Racional& b) {
  Racional result ((a.num_ * b.num_), (a.den_ * b.den_));
  return result;
}

Racional operator/(const Racional& a, const Racional& b) {
  Racional result ((a.num_ * b.den_), (a.den_ * b.num_));
  return result;
}

Number* Racional::add(const Number* b) const {
  return NULL;
} 

Number* Racional::subtract(const Number* b) const {
  return NULL;
} 

Number* Racional::multiply(const Number* b) const {
  return new Racional ((*this) * dynamic_cast<const Racional&>(*b));
} 
  
Number* Racional::divide(const Number* b) const {
  return new Racional ((*this) / dynamic_cast<const Racional&>(*b));
}

Number* Racional::module(const Number* b) const {
  return NULL;
}

Number* Racional::power(const Number* b) const {
  return NULL;
} 

Racional::operator BigInt<2>() const {
  return BigInt<2> ();
} 

Racional::operator BigInt<8>() const {
  return BigInt<8> ();
} 

Racional::operator BigInt<10>() const {
  return BigInt<10> ();
} 

Racional::operator BigInt<16>() const {
  return BigInt<16> ();
} 