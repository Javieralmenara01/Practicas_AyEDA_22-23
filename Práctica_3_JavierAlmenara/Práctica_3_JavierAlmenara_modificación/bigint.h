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
 * @file: bigint.h
 *    La clase BigInt nos permite operar y representar números enteros.
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

/**
 * Clase BigInt
 * @brief Permite la representación de números grandes
 */
template<size_t Base>
class BigInt : public Number {
 public:
  /// Constructores
  BigInt(long n = 0);
  BigInt(const std::string&);
  BigInt(const char*);
  BigInt(const BigInt<Base>&); /// Constructor de copia
  /// Creación de los objetos en memoria dinámica
  static Number* create(size_t base, const std::string& s);
  /// Operadores de conversión de tipo 
  operator BigInt<2>() const override; 
  operator BigInt<8>() const override; 
  operator BigInt<10>() const override; 
  operator BigInt<16>() const override; 
  /// Asignación
  BigInt<Base>& operator=(const BigInt<Base>&);
  /// Inserción y extracción en flujo
  template<size_t U>
  friend std::ostream& operator<<(std::ostream&, const BigInt<U>&); 
  template<size_t U>
  friend std::istream& operator>>(std::istream&, BigInt<U>&);
  /// Operadores de inserción y extracción de flujo
  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&) override;
  /// Getters
  std::vector<char> digits() const { return digits_; }
  bool is_negative() const { return is_negative_; }
  /// Setters
  void set_digits(const std::vector<char>& digits) { digits_ = digits; }
  void set_is_negative(const bool is_negative) { is_negative_ = is_negative; }
  /// Accesor
  int sign() const; /// Signo: 1 o -1
  char operator[](int) const; /// Acceso al i-ésimo dígito
  /// Comparación
  friend bool operator== <Base>(const BigInt<Base>&, const BigInt<Base> &); 
  bool operator!=(const BigInt<Base>&) const;
  friend bool operator> <Base>(const BigInt<Base>&, const BigInt<Base> &); 
  bool operator>=(const BigInt<Base> &) const;
  friend bool operator< <Base>(const BigInt<Base>&, const BigInt<Base>&); 
  bool operator<=(const BigInt<Base>&) const;
  /// Incremento/decremento
  BigInt<Base>& operator++(); /// Pre-incremento
  BigInt<Base> operator++(int); /// Post-incremento
  BigInt<Base>& operator--(); /// Pre-decremento
  BigInt<Base> operator--(int); /// Pre-decremento 
  /// Operadores aritméticas BigInt
  friend BigInt<Base> operator+ <Base>(const BigInt<Base>&, const BigInt<Base>&);
  BigInt<Base> operator-(const BigInt<Base> &) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base>&) const;
  friend BigInt<Base> operator/ <Base>(const BigInt<Base>&, const BigInt<Base>&);
  BigInt<Base> operator%(const BigInt<Base>&) const;
  template <size_t U>
  friend BigInt<Base> pow(const BigInt<Base>&, const BigInt<Base>&);
  /// Operaciones aritméticas Number
  Number* add(const Number*) const override; 
  Number* subtract(const Number*) const override; 
  Number* multiply(const Number*) const override; 
  Number* divide(const Number*) const override; 
  Number* module(const Number*) const override; 
  Number* power(const Number*) const override; 
  /// Otros
  friend BigInt<Base> absolute_sum <Base>(const BigInt<Base>&, const BigInt<Base>&);
  friend BigInt<Base> absolute_substraction <Base>(const BigInt<Base>&, const BigInt<Base>&);
  friend bool absolute_value <Base>(const BigInt<Base>&, const BigInt<Base>&);
  std::size_t base = Base;
 private:
  std::vector<char> digits_;
  bool is_negative_ = false;
};

/**
 * Absolute increase
 * @brief Permite incrementar un número de forma absoluta
 * @param digits_ : vector de dígitos
 * @param base : base del número en cuestión
 */
inline std::vector<char> absolute_increase(const std::vector<char>& digits_, size_t base) {
  std::vector<char> digits = digits_;
  int carry = 1;
  for (int i = 0; i < (int)digits.size(); i++) {
    digits[i] += carry;
    if ((short)digits[i] < (short)base) {
      carry = 0;
      break;
    }
    digits[i] = 0;
  }
  if (carry) {
    digits.push_back(1);
  }
  return digits;
}

/**
 * Absolute increase
 * @brief Permite decremenar un número de forma absoluta almacenado en un vector de char
 * @param digits_ : vector de dígitos
 * @param base : base del número en cuestión
 */
inline std::vector<char> absolute_decrease(const std::vector<char>& digits_, size_t base) {
  std::vector<char> digits = digits_;
  int carry = 1;
  for (int i = 0; i < (int)digits.size(); i++) {
    digits[i] -= carry;
    if ((short)digits[i] >= 0) {
      carry = 0;
      break;
    }
    digits[i] = base - 1;
  }
  while (digits.size() > 1 && (short)digits.back() == 0) {
    digits.pop_back();
  }
  return digits;
}

/**
 * Absolute sum
 * @brief Permite la suma de dos números de forma absoluta
 * @param a : primer sumando
 * @param b : segundo sumando
 */
template<size_t Base>
BigInt<Base> absolute_sum(const BigInt<Base>& a, const BigInt<Base>& b) {
  BigInt<Base> c;
  c.digits_.clear();
  int carry = 0;
  int size_a = a.digits_.size();
  int size_b = b.digits_.size();
  for (int i = 0; i < std::max(size_a, size_b); i++) {
    int d1 = (i < size_a) ? a.digits_[i] : 0;
    int d2 = (i < size_b) ? b.digits_[i] : 0;
    c.digits_.push_back((d1 + d2 + carry) % Base);
    carry = (d1 + d2 + carry) / Base;
  }
  if (carry) {
    c.digits_.push_back(carry);
  }
  return c;
}

/**
 * Absolute substraction
 * @brief Permite la resta de dos números de forma absoluta
 * @param a : minuendo
 * @param b : sustraendo
 */
template<size_t Base>
BigInt<Base> absolute_substraction(const BigInt<Base>& a, const BigInt<Base>& b)  {
  BigInt<Base> c;
  c.digits_.clear();
  int carry = 0;
  int size_a = a.digits_.size();
  int size_b = b.digits_.size();
  for (int i = 0; i < size_b; i++) {
    int d1 = a.digits_[i];
    int d2 = b.digits_[i];
    if (d1 - carry < d2) {
      c.digits_.push_back((short)((d1 + Base - carry) - d2));
      carry = 1;
    } else {
      c.digits_.push_back(d1 - carry - d2);
      carry = 0;
    }
  }
  for (int i = size_b; i < size_a; i++) {
    int d1 = a.digits_[i];
    if (d1 - carry < 0) { 
      c.digits_.push_back(d1 + Base - carry);
      carry = 1;
    } else {
      c.digits_.push_back(d1 - carry);
      carry = 0;
    }
  }
  while (c.digits_.size() > 1 && (short)c.digits_.back() == 0) {
    c.digits_.pop_back();
  }
  return c;
}

/**
 * Absolute Value >
 * @brief Nos permite comparar números de forma absoluta para determinar su el primer número es mayor que el segundo
 * @param a : primer número de la clase BigInt
 * @param b : segundo número de la clase BigInt
 */
template<size_t Base>
bool absolute_value(const BigInt<Base>& a, const BigInt<Base>& b) {
  if (a.digits_.size() > b.digits_.size()) {
    return true;
  } else if (a.digits_.size() < b.digits_.size()) {
    return false;
  }
  for (int i = a.digits_.size() - 1; i >= 0; i--) {
    if (a[i] != b[i]) {
      if (a[i] > b[i]) {
        return true;
      } else {
        return false;
      }
    }
  }
  if (std::max(a.digits_.size(), b.digits_.size()) == a.digits_.size()) {
    return true;
  }
  return false;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo long
 * @param long : Objeto del tipo long
 */
template<size_t Base>
BigInt<Base>::BigInt(long n) {
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  if (n < 0) {
    is_negative_ = true;
    n = -n;
  }
  do {
    digits.push_back(n % Base);
    n /= Base;
  } while (n > 0);
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para cadenas
 * @param s : Objeto del tipo string
 */
template<size_t Base>
BigInt<Base>::BigInt(const std::string& s) {
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  int j = 0;
  if (s[0] == '-') {
    is_negative_ = true;
    ++j;
  }
  bool begin_not_zero = false;
  std::string aux;
  for (size_t i = j; i < s.size() - 1; i++) {
    if (s[i] != '0' && !begin_not_zero) {
      begin_not_zero = true;
      aux.push_back(s[i]);
    } else if (begin_not_zero) {
      aux.push_back(s[i]);
    }
  }
  aux.push_back(s[s.size() - 1]);
  std::string result = aux;
  for (int i = result.size() - 1; i >= 0; i--) {
    if (result[i] >= 'A') {
      digits.push_back(result[i] - 'A' + 10);
    } else {
      digits.push_back(result[i] - '0');
    }
  }
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo char* (array de char)
 * @param n : Objeto del tipo char*
 */
template<size_t Base>
BigInt<Base>::BigInt(const char* n) {
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  int j = 0;
  if (n[0] == '-') {
    is_negative_ = true;
    j++;
  }
  bool begin_not_zero = false;
  std::string aux;
  for (size_t i = j; i < strlen(n) - 1; i++) {
    if (n[i] != '0' && !begin_not_zero) {
      begin_not_zero = true;
    }
    if (begin_not_zero) {
      aux.push_back(n[i]);
    }
  }
  aux.push_back(n[strlen(n) - 1]);
  n = aux.c_str();
  for (int i = strlen(n) - 1; i >= j; i--) {
    if (n[i] >= 'A') {
      digits.push_back(n[i] - 'A' + 10);
    } else {
      digits.push_back(n[i] - '0');
    }
  }
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para números de la clase BigInt
 * @param n : Objeto del tipo BigInt
 */
template<size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
}

/**
 * @brief Sobrecarga del operador de asignación de la clase BigInt
 * @param n : Objeto del tipo BigInt
 */
template<size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
  return *this;
}

/**
 * @brief Sobrecarga del operador de extracción de flujo de la clase BigInt
 * @param out : Objeto del tipo flujo estándar de salida
 * @param a : Objeto del tipo BigInt
 */
template<size_t U>
std::ostream& operator<<(std::ostream& out, const BigInt<U>&a) {
  out << U << ", ";
  if (a.is_negative()) {
    out << "-";
  }
  for (int i = a.digits().size() - 1; i >= 0; i--) {
    if ((short)a.digits()[i] < 10) {
      out << (char)('0' + a.digits()[i]);
    } else {
      out << (char)('A' + a.digits()[i] - 10);
    }
  }
  return out;
}

/**
 * @brief Sobrecarga del operador de inserción de flujo de la clase BigInt
 * @param in : Objeto del tipo flujo estándar de entrada
 * @param a : Objeto del tipo BigInt
 */
template<size_t U>
std::istream& operator>>(std::istream& in, BigInt<U>& a) {
  std::string s;
  in >> s;
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  int j = 0;
  if (s[0] == '-') {
    a.set_is_negative(true);
    ++j;
  }
  for (int i = s.size() - 1; i >= j; i--) {
    if (s[i] >= 'A') {
      digits.push_back(10 + s[i] - '0');
    } else {
      digits.push_back(s[i] - '0');
    }
  }
  a.set_digits(digits);
  return in;
}


/**
 * @brief Función que nos permite escribir un objeto por la salida estándar
 * @param out : Objeto del tipo flujo estándar de salida
 */
template<size_t Base>
std::ostream& BigInt<Base>::write(std::ostream& out) const {
  out << *this;
  return out;
}

/**
 * @brief Función que nos permite leer un objeto por la entrada estándar
 * @param in : Objeto del tipo flujo estándar de entrada
 */
template<size_t Base>
std::istream& BigInt<Base>::read(std::istream& in) {
  in >> *this;
  return in;
}


/**
 * Sign
 * @brief Permite saber el síngo del objeto invocante
 */
template<size_t Base>
int BigInt<Base>::sign() const {
  return (is_negative_ ? -1 : 1);
}

/**
 * Sobrecarga del operador []
 * @brief Permite obtener el valor en el objeto en la posición indicada
 */
template<size_t Base>
char BigInt<Base>::operator[](int i) const {
  assert(i >= 0 && i < (int)digits_.size());
  return digits_[i];
}

/**
 * Sobrecarga del operador ==
 * @brief Permite obtener si ambos objetos de la clase BigInt son iguales
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
bool operator==(const BigInt<Base>& a, const BigInt<Base> & b) {
  if ((a.is_negative_ != b.is_negative_) || (a.digits_.size() != b.digits_.size())) {
    return false;
  }
  for (size_t i = 0; i < a.digits_.size(); i++) {
    if ((short)a[i] != (short)b[i]) {
      return false;
    }
  }
  return true;
}

/**
 * Sobrecarga del operador !=
 * @brief Permite obtener si ambos objetos de la clase BigInt no son iguales
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& b) const {
  return !(*this == b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es mayor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
bool operator>(const BigInt<Base>& a, const BigInt<Base> & b) {
  if (a.is_negative_ != b.is_negative_) {
    if (a.is_negative_ && !b.is_negative_) {
      return false;
    } else {
      return true;
    }
  }
  if (a.digits_.size() > b.digits_.size()) {
    return true;
  } else if (a.digits_.size() < b.digits_.size()) {
    return false;
  }
  for (int i = std::min(a.digits_.size(), b.digits_.size()) - 1; i >= 0; i--) {
    if (a[i] != b[i]) {
      if (a[i] > b[i]) {
        return true;
      } else {
        return false;
      }
    }
  }
  return true;
}

/**
 * Sobrecarga del operador >=
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es mayor o igual que el segundo
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> & b) const {
  return (*this == b || *this > b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
bool operator<(const BigInt<Base>& a, const BigInt<Base>& b) {
  return !(a >= b);
}

/**
 * Sobrecarga del operador >=
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor o igual que el segundo
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& b) const {
  return (*this == b || *this < b);
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
template<size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {
  std::vector<char> &digits = this->digits_;
  if (is_negative_ == true) {
    digits = absolute_decrease(digits_, Base);
    // Declaración de "-0"
    BigInt<Base> n1;
    n1 = -n1;
    if (n1 == *this) {
      is_negative_ = false;
    }
  } else {
    digits = absolute_increase(digits_, Base);
  }
  return *this;
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
template<size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {
  BigInt<Base> temp(*this);
  ++(*this);
  return temp;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
template<size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {
  std::vector<char> &digits = this->digits_;
  if (is_negative_ == false) {
    digits = absolute_decrease(digits_, Base);
  } else {
    digits = absolute_increase(digits_, Base);
  }
  return *this;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
template<size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {
  BigInt<Base> temp(*this);
  --(*this);
  return temp;
}

/**
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
BigInt<Base> operator+(const BigInt<Base>& a, const BigInt<Base>& b) {
  BigInt<Base> c;
  if (a == c || b == c) {
    if (a == c) {
      return b;
    } else {
      return a;
    }
  } else if (a.is_negative_ == b.is_negative_) {
    c = absolute_sum(a,b);
    if (a.is_negative_) {
      c = -c;
    }
  } else {
    c = absolute_substraction(a, b);
    if (a > b) {
      if (!absolute_value(a, b)) {
        c = -c;
      }
    } else {
      if (absolute_value(a, b)) {
        c = -c;
      }
    }
  }
  return c;
}

/**
 * Sobrecarga del operador -
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base> &b) const {
  BigInt<Base> c;
  if (*this == c || b == c) {
    if (*this == c) {
      c = -b;
    } else {
      c = -*this;
    }
    return c;
  } else if (is_negative_ == b.is_negative_) {
    if (is_negative_ == false) {
      if (!absolute_value(*this, b)) {
        c = absolute_substraction(b, *this);
        c = -c;
      } else {
        c = absolute_substraction(*this, b);
      }
    } else {
      if (absolute_value(*this, b)) {
        c = absolute_substraction(*this, b);
        c = -c;
      } else {
        c = absolute_substraction(b, *this);
      }
    }
  } else {
    if (is_negative_ && !b.is_negative_) {
      c = absolute_sum(*this, b);
      if (absolute_value(*this, b)) {
        c = -c;
      }
    } else {
      c = absolute_sum(*this, b);
      if (!absolute_value(*this, b)) {
        c = -c;
      }
    }
  }
  return c;
}

/**
 * Sobrecarga del operador -
 * @brief Permite cambiar el signo del objeto invocante
 */
template<size_t Base>
BigInt<Base> BigInt<Base>::operator-() const {
  bool condition = !(is_negative_);
  BigInt<Base> n = *this;
  n.is_negative_ = condition;
  return n;
}

/**
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& b) const {
  BigInt<Base> c, d, e;
  bool cond_sum = false;
  if (*this == c || b == c) {
    return c;
  }
  if (b < d) {
    cond_sum = true;
  }
  e = b;
  while (d != e) {
    c = absolute_sum(c, *this);
    if (cond_sum) {
      e++;
    } else {
      e--;
    }
  }
  if (is_negative_ != b.is_negative_) {
    c.is_negative_ = true;
  }
  return c;
}

/**
 * Sobrecarga del operador /
 * @brief Permite obtener el cociente dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
BigInt<Base> operator/(const BigInt<Base>& a, const BigInt<Base>& b) {
  BigInt<Base> c, d, e;
  if (b == c) {
    BigIntException exception;
    throw exception.BigIntDivisionByZero();
  }
  if (a == c) {
    return c;
  }
  bool sign_a = a.is_negative_, sign_b = b.is_negative_, condition = false;
  if (a.is_negative_) {
    c = -a;
  } else {
    c = a;
  }
  if (b.is_negative_) {
    d = -b;
  } else {
    d = b;
  }
  while (c >= d) {
    condition = true;
    c = absolute_substraction(c, d);
    ++e;
  }
  if ((sign_a != sign_b) && condition) {
    e.is_negative_ = true;
  }
  return e;
}

/**
 * Sobrecarga del operador %
 * @brief Permite obtener el módulo dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base>& b) const {
    BigInt<Base> c, d, e, f;
  if (b == c) {
    BigIntException exception;
    throw exception.BigIntDivisionByZero();
  }
  if (*this == c) {
    return c;
  }
  bool condition = false;
  if (is_negative_) {
    c = -(*this);
  } else {
    c = *this;
  }
  if (b.is_negative_) {
    d = -b;
  } else {
    d = b;
  }
  while (c >= d) {
    condition = true;
    c = absolute_substraction(c, d);
    ++e;
  }
  if (condition && (c != f)) {
    if (is_negative_) {
      c.is_negative_ = true;
    }
  }
  return c;
}

/**
 * Power
 * @brief Permite elevar la potencia de un objeto de la clase BigInt elevado a otro objeto
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
BigInt<Base> pow(const BigInt<Base>& a, const BigInt<Base>& b) {
  BigInt<Base> c(1), d;
  if (b.is_negative()) {
    BigIntException exception;
    throw exception.BigIntIntegerRepresentation();
  }
  while (d < b) {
    c = a * c;
    ++d;
  }
  return c;
}

/**
 * Método Add
 * @brief Permite sumar dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
Number* BigInt<Base>::add(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<Base>*>(this);
  if (p) {
    return new BigInt<Base> (*this + (BigInt<Base>)*b);
  }
  return NULL;
}

/**
 * Método Subtract
 * @brief Permite restar dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
Number* BigInt<Base>::subtract(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<Base>*>(this);
  if (p) {
    return new BigInt<Base> (*this - (BigInt<Base>)*b);
  }
  return NULL;
}

/**
 * Método Multiply
 * @brief Permite multiplicar dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
Number* BigInt<Base>::multiply(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<Base>*>(this);
  if (p) {
    return new BigInt<Base> (*this * (BigInt<Base>)*b);
  }
  return NULL;
}

/**
 * Método Divide
 * @brief Permite dividir dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
Number* BigInt<Base>::divide(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<Base>*>(this);
  if (p) {
    return new BigInt<Base> (*this / (BigInt<Base>)*b);
  }
  return NULL;;
}

/**
 * Método Module
 * @brief Permite obtener el módulo dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
Number* BigInt<Base>::module(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<Base>*>(this);
  if (p) {
    return new BigInt<Base> (*this % (BigInt<Base>)*b);
  }
  return NULL;
}

/**
 * Método Power
 * @brief Permite elevar a la potencia, dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
template<size_t Base>
Number* BigInt<Base>::power(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<Base>*>(this);
  if (p) {

    return new BigInt<Base> (pow(*this, (BigInt<Base>)*b));
  }
  return NULL;
}

/**
 * Especialización de plantilla par la clase BigInt<2> 
 * @brief Permite la representación de números grandes en base 2
 */
template<>
class BigInt<2> : public Number {
 public: 
  /// Constructores
  BigInt(long n = 0);
  BigInt(const std::string&);
  BigInt(const char*);
  BigInt(const BigInt<2>&); /// Constructor de copia
  /// Creación de los objetos en memoria dinámica
  static Number* create(size_t base, const std::string& s);
  /// Getter
  std::vector<bool> digits() const { return digits_; }
  /// Setter
  void set_digits(const std::vector<bool>& digits) { digits_ = digits; }
  /// Transformadores de Base
  operator BigInt<2>() const override; // código de conversión de binario a binario  
  operator BigInt<8>() const override; // código de conversión de binario a octal 
  operator BigInt<10>() const override; // código de conversión de binario a decimal 
  operator BigInt<16>() const override; // código de conversión de binario a hexadecimal 
  /// Asignación
  BigInt<2>& operator=(const BigInt<2>&);
  /// Inserción y extracción en flujo
  friend std::ostream& operator<< <2>(std::ostream&, const BigInt<2>&); 
  friend std::istream& operator>> <2>(std::istream&, BigInt<2>&);
  /// Operadores de inserción y extracción de flujo
  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&) override;
  /// Accesor
  bool operator[](int) const; /// Acceso al i-ésimo dígito
  /// Comparación
  friend bool operator== <2>(const BigInt<2>&, const BigInt<2> &); 
  bool operator!=(const BigInt<2>&) const;
  friend bool operator> <2>(const BigInt<2>&, const BigInt<2> &); 
  bool operator>=(const BigInt<2> &) const;
  friend bool operator< <2>(const BigInt<2>&, const BigInt<2>&); 
  bool operator<=(const BigInt<2>&) const;
  /// Incremento/decremento
  BigInt<2>& operator++(); /// Pre-incremento
  BigInt<2> operator++(int); /// Post-incremento
  BigInt<2>& operator--(); /// Pre-decremento
  BigInt<2> operator--(int); /// Pre-decremento 
  /// Operadores Aritméticos BigInt<2>
  friend BigInt<2> operator+ <2>(const BigInt<2>&, const BigInt<2>&); 
  BigInt<2> operator-(const BigInt<2> &) const;
  BigInt<2> operator-() const;
  BigInt<2> operator*(const BigInt<2>&) const;
  friend BigInt<2> operator/ <2>(const BigInt<2>&, const BigInt<2>&); 
  BigInt<2> operator%(const BigInt<2>&) const;
  friend BigInt<2> pow(const BigInt<2>&, const BigInt<2>&);
  /// Operadores Aritméticos Number*
  Number* add(const Number*) const override; 
  Number* subtract(const Number*) const override; 
  Number* multiply(const Number*) const override; 
  Number* divide(const Number*) const override; 
  Number* module(const Number*) const override; 
  Number* power(const Number*) const override;
  std::size_t base = 2;
 private:
  std::vector<bool> digits_;
  bool is_negative_;
};

/**
 * Complement Vector
 * @brief: Complementar un vector de bool, cuyo propósito es representar los dígitos de un número en base 2, a complemento a 2.
 * @param digits_to_c2: dígitos de un número en base 2, representación C2.
 */
inline std::vector<bool> compl_vector(const std::vector<bool>& digits_to_c2) {
  std::vector<bool> digits = digits_to_c2, nw_digits;
  bool condition = false;
  int num_of_ones = 0;
  for (int i = 0; i < (int)digits.size(); i++) {
    if (!condition && digits[i]) {
      condition = true;
      nw_digits.push_back(digits[i]);
    } else if (condition) {
      nw_digits.push_back(!digits[i]);
    } else {
      nw_digits.push_back(digits[i]);
    }
    if (digits[i]) {
      ++num_of_ones;
    }
  }
  return nw_digits;
}

/**
 * Absolute Increase Base 2 
 * @brief: Permite incrementar un número en base 2, de forma absoluta, dados sus dígitos en un vector de bool.
 * @param vector_of_digits: dígitos de un número en base 2, representación C2.
 */
inline std::vector<bool> absolute_increase_2(const std::vector<bool>& vector_of_digits) {
  std::vector<bool> digits_ = vector_of_digits;
  bool carry = true;
  for (int i = 0; i < (int)digits_.size(); ++i) {
    if (!carry) {
      break;
    }
    if (digits_[i] == false) {
      digits_[i] = true;
      carry = false;
    } else {
      digits_[i] = false;
      carry = true;
    }
  }
  return digits_;
}

/**
 * Absolute Decrease Base 2 
 * @brief: Permite decrementar un número en base 2, de forma absoluta, dados sus dígitos en un vector de bool.
 * @param vector_of_digits: dígitos de un número en base 2, representación C2.
 */
inline std::vector<bool> absolute_decrease_2(const std::vector<bool>& vector_of_digits) {
  std::vector<bool> digits_ = vector_of_digits;
  for (int i = 0; i < (int)digits_.size(); ++i) {
    if (digits_[i] == true) {
      digits_[i] = false;
      break;
    } else {
      digits_[i] = true;
    }
  }
  return digits_;
}

/**
 * Absolute Sum Base 2 
 * @brief: Permite sumar dos números en base 2, de forma absoluta, dados sus dígitos en un vector de bool.
 * @param a: número en base 2, representación C2.
 * @param b: número en base 2, representación C2.
 */
inline BigInt<2> absolute_sum_2(const BigInt<2>& a, const BigInt<2>& b) {
  std::vector<bool> sum;
  std::vector<bool> digits_a = a.digits();
  std::vector<bool> digits_b = b.digits();
  int n = digits_a.size();
  int m = digits_b.size();
  int i = 0, j = 0;
  bool carry = false, condition = (digits_a[n - 1] == digits_b[m - 1]);
  while (i < n && j < m) {
    if (digits_a[i] == false && digits_b[j] == false) {
      sum.push_back(carry);
      carry = false;
    } else if (digits_a[i] == true && digits_b[j] == true) {
      sum.push_back(carry);
      carry = true;
    } else {
      sum.push_back(!carry);
    }
    i++;
    j++;
  }
  while (i < n) {
    if (digits_a[i] == false) {
      sum.push_back(carry);
      carry = false;
    } else {
      sum.push_back(!carry);
    }
    i++;
  }
  while (j < m) {
    if (digits_b[j] == false) {
      sum.push_back(carry);
      carry = false;
    } else {
      sum.push_back(!carry);
    }
    j++;
  }
  /// Línea por comprobar 
  if (carry && condition) {
    sum.push_back(true);
  }
  /// -------------------
  BigInt<2> num_final;
  num_final.set_digits(sum);
  return num_final;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo long
 * @param long : Objeto del tipo long
 */
inline BigInt<2>::BigInt(long n) {
  std::vector<bool> digits;
  bool is_negative = false;
  /// Comprobar si el número es negativo
  if (n < 0) {
    is_negative = true;
    n = -n;
  }
  do {
    digits.push_back(n % 2);
    n /= 2;
  } while (n > 0);
  digits.push_back(false);
  if (is_negative) {
    digits = compl_vector(digits);
  }
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para cadenas
 * @param s : Objeto del tipo string
 */
inline BigInt<2>::BigInt(const std::string& s) {
  std::vector<bool> digits;
  bool is_negative = false;
  /// Comprobar si el número es negativo
  int j = 0;
  if (s[0] == '-') {
    is_negative = true;
    ++j;
  }
  bool begin_not_zero = false;
  std::string aux;
  for (size_t i = j; i < s.size() - 1; i++) {
    if (s[i] != '0' && !begin_not_zero) {
      begin_not_zero = true;
    }
    if (begin_not_zero) {
      aux.push_back(s[i]);
    }
  }
  aux.push_back(s[s.size() - 1]);
  std::string result = aux;
  for (int i = result.size() - 1; i >= j; i--) {
    if (result[i] == '0') {
      digits.push_back(false);
    } else if (result[i] == '1') {
      digits.push_back(true);
    } else {
      BigIntException exception;
      throw exception.BigIntBadDigit();
    }
  }
  digits.push_back(false);
  if (is_negative) {
    digits = compl_vector(digits);
  }
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo char* (array de char)
 * @param n : Objeto del tipo char*
 */
inline BigInt<2>::BigInt(const char* n) {
  std::vector<bool> digits;
  /// Comprobar si el número es negativo
  int j = 0;
  bool is_negative = false;
  if (n[0] == '-') {
    is_negative = true;
    j++;
  }
  bool begin_not_zero = false;
  std::string aux;
  for (size_t i = j; i < strlen(n) - 1; i++) {
    if (n[i] != '0' && !begin_not_zero) {
      begin_not_zero = true;
    }
    if (begin_not_zero) {
      aux.push_back(n[i]);
    }
  }
  aux.push_back(n[strlen(n) - 1]);
  n = aux.c_str();
  for (int i = strlen(n) - 1; i >= j; i--) {
    if (n[i] == '0') {
      digits.push_back(false);
    } else if (n[i] == '1') {
      digits.push_back(true);
    } else {
      BigIntException exception;
      throw exception.BigIntBadDigit();
    }
  }
  digits.push_back(false);
  if (is_negative) {
    digits = compl_vector(digits);
  }
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para números de la clase BigInt
 * @param n : Objeto del tipo BigInt
 */
inline BigInt<2>::BigInt(const BigInt<2>& n) {
  digits_ = n.digits_;
}

/**
 * @brief Sobrecarga del operador de asignación de la clase BigInt<2>
 * @param n : Objeto del tipo BigInt
 */
inline BigInt<2>& BigInt<2>::operator=(const BigInt<2>& n) {
  digits_ = n.digits_;
  return *this;
}

/**
 * @brief Sobrecarga del operador de extracción de flujo de la clase BigInt
 * @param out : Objeto del tipo flujo estándar de salida
  * @param a : Objeto del tipo BigInt
 */
template<>
inline std::ostream& operator<< <2>(std::ostream& out, const BigInt<2>& a) {
  out << "2, ";
  for (int i = a.digits_.size() - 1; i >= 0; i--) {
    out << a.digits_[i];
  }
  return out;
}

/**
 * @brief Sobrecarga del operador de inserción de flujo de la clase BigInt
 * @param in : Objeto del tipo flujo estándar de entrada
 * @param a : Objeto del tipo BigInt
 */
template<>
inline std::istream& operator>> <2>(std::istream& in, BigInt<2>& a) {
  std::string s;
  in >> s;
  std::vector<bool> digits;
  bool is_negative = false;
  /// Comprobar si el número es negativo
  int j = 0;
  if (s[0] == '-') {
    is_negative = true;
    ++j;
  }
  bool begin_not_zero = false;
  std::string aux;
  for (size_t i = j; i < s.size() - 1; i++) {
    if (s[i] != '0' && !begin_not_zero) {
      begin_not_zero = true;
    }
    if (begin_not_zero) {
      aux.push_back(s[i]);
    }
  }
  aux.push_back(s[s.size() - 1]);
  s = aux;
  for (int i = s.size() - 1; i >= j; i--) {
    if (s[i] == '0') {
      digits.push_back(false);
    } else if (s[i] == '1') {
      digits.push_back(true);
    } else {
      BigIntException exception;
      throw exception.BigIntBadDigit();
    }
  }
  if (is_negative) {
    digits = compl_vector(digits);
  }
  a.set_digits(digits);
  return in;
}

/**
 * @brief Función que nos permite escribir un objeto por la salida estándar
 * @param out : Objeto del tipo flujo estándar de salida
 */
inline std::ostream& BigInt<2>::write(std::ostream& out) const {
  out << *this;
  return out;
}

/**
 * @brief Función que nos permite leer un objeto por la entrada estándar
 * @param in : Objeto del tipo flujo estándar de entrada
 */
inline std::istream& BigInt<2>::read(std::istream& in) { 
  in >> *this;
  return in;
}
  
/**
 * Sobrecarga del operador []
 * @brief Permite obtener el valor en el objeto en la posición indicada
 */
inline bool BigInt<2>::operator[](int i) const {
  assert(i >= 0 && i < (int)digits_.size());
  return digits_[i];
}

/**
 * Sobrecarga del operador ==
 * @brief Permite obtener si ambos objetos de la clase BigInt son iguales
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline bool operator==(const BigInt<2>& a, const BigInt<2> & b) {
  if ((a.digits()[a.digits().size() - 1] != b.digits()[b.digits().size() - 1])) {
    return false;
  }
  for (size_t i = 0; i < std::min(a.digits().size(), b.digits().size()); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  if (a.digits().size() != b.digits().size()) {
    if (a.digits().size() > b.digits().size()) {
      int diff = a.digits().size() - b.digits().size();
      for (int i = 0; i < diff; i++) {
        if (a.digits()[a.digits().size() - 1 - i] != b.digits()[b.digits().size()]) {
          return false;
        }
      }
    } else {
      int diff = b.digits().size() - a.digits().size();
      for (int i = 0; i < diff; i++) {
        if (b.digits()[b.digits().size() - 1 - i] != a.digits()[a.digits().size()]) {
          return false;
        }
      }
    }
  }
  return true;
}

/**
 * Sobrecarga del operador !=
 * @brief Permite obtener si ambos objetos de la clase BigInt no son iguales
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline bool BigInt<2>::operator!=(const BigInt<2>& b) const {
  return !(*this == b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es mayor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline bool operator>(const BigInt<2>& a, const BigInt<2> & b) {
  if (a.digits()[a.digits().size() - 1] != b.digits()[b.digits().size() - 1]) {
    if (a.digits()[a.digits().size() - 1] && !b.digits()[b.digits().size() - 1]) {
      return false;
    } else {
      return true;
    }
  }
  BigInt<2> c, d;
  c = a;
  d = b;
  if (a.digits()[a.digits().size() - 1] == true) {
    c = -a;
    d = -b;
  }
  std::vector<bool> digits_c = c.digits(), digits_d = d.digits();
  if (c.digits().size() != d.digits().size()) {
    if (c.digits().size() < d.digits().size()) {
      int difference = (d.digits().size() - c.digits().size());
      bool bms = c.digits()[c.digits().size() - 1];
      for (int i = 0; i < difference; i++) {
        digits_c.push_back(bms);
      }
    } else {
      int difference = (c.digits().size() - d.digits().size());
      bool bms = d.digits()[d.digits().size() - 1];
      for (int i = 0; i < difference; i++) {
        digits_d.push_back(bms);
      }
    }
  }
  c.set_digits(digits_c);
  d.set_digits(digits_d);
  for (int i = c.digits().size() - 1; i >= 0; i--) {
    if (c[i] != d[i]) {
      if (c[i] > d[i]) {
        return true;
      } else {
        return false;
      }
    }
  }
  if (a == b) {
    return false;
  }
  return true;
}

/**
 * Sobrecarga del operador >=
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es mayor o igual que el segundo
 * @param b : Objeto del tipo BigInt
 */
inline bool BigInt<2>::operator>=(const BigInt<2> & b) const {
  return (*this == b || *this > b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline bool operator<(const BigInt<2>& a, const BigInt<2>& b) {
  return !(a >= b);
}

/**
 * Sobrecarga del operador >=
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor o igual que el segundo
 * @param b : Objeto del tipo BigInt
 */
inline bool BigInt<2>::operator<=(const BigInt<2>& b) const {
  return (*this == b || *this < b);
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
inline BigInt<2>& BigInt<2>::operator++() {
  std::vector<bool> &digits = this->digits_;
  bool condition_is_positive = false;
  if (digits[digits.size() - 1] == false) {
    condition_is_positive = true;
  }
  digits = absolute_increase_2(digits);
  if ((digits[digits.size() - 1]) && condition_is_positive) {
    digits.push_back(false);
  } else if (!(digits[digits.size() - 1]) && !condition_is_positive) {
    bool begin_not_zero = false;
    for (size_t i = (digits.size() - 1); i > 0; i--) {
      if (digits[i] != false && !begin_not_zero) {
        begin_not_zero = true;
      }
      digits.pop_back();
    }
  }
  return *this;
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
inline BigInt<2> BigInt<2>::operator++(int) {
  BigInt<2> temp(*this);
  ++(*this);
  return temp;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
inline BigInt<2>& BigInt<2>::operator--() {
  std::vector<bool> &digits = this->digits_;
  BigInt<2> c;
  if (*this == c) {
    digits.pop_back();
    digits.pop_back();
    digits.push_back(true);
    digits.push_back(true);
    return *this;
  }
  digits = absolute_decrease_2(digits);
  return *this;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
inline BigInt<2> BigInt<2>::operator--(int) {
  BigInt<2> temp(*this);
  --(*this);
  return temp;
}

/**
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline BigInt<2> operator+(const BigInt<2>& a, const BigInt<2>& b) {
  BigInt<2> c, d, e;
  std::vector<bool> digits_a = a.digits(), digits_b = b.digits();
  if (a.digits().size() != b.digits().size()) {
    if (a.digits().size() < b.digits().size()) {
      int difference = (b.digits().size() - a.digits().size());
      bool bms = a.digits()[a.digits().size() - 1];
      for (int i = 0; i < difference; i++) {
        digits_a.push_back(bms);
      }
    } else {
      int difference = (a.digits().size() - b.digits().size());
      bool bms = b.digits()[b.digits().size() - 1];
      for (int i = 0; i < difference; i++) {
        digits_b.push_back(bms);
      }
    }
  }
  d.set_digits(digits_a);
  e.set_digits(digits_b);
  c = absolute_sum_2(d, e);
  digits_a = c.digits();
  if (a.digits()[a.digits().size() - 1] == b.digits()[b.digits().size() - 1]) {
    digits_a = c.digits();
    if (a.digits()[a.digits().size() - 1] != c.digits()[c.digits().size() - 1]) {
      if (a.digits()[a.digits().size() - 1]) {
        digits_a.push_back(true);
      } else {
        digits_a.push_back(false);
      }
    }
    c.set_digits(digits_a);
  }
  return c;
}

/**
 * Sobrecarga del operador -
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline BigInt<2> BigInt<2>::operator-(const BigInt<2> &b) const {
  BigInt<2> c, d;
  d = -b;
  c = *this + d;
  return c;
}

/**
 * Sobrecarga del operador -
 * @brief Permite cambiar el signo del objeto invocante
 */
inline BigInt<2> BigInt<2>::operator-() const {
  std::vector<bool> digits_ = digits(), nw_digits;
  bool condition = false;
  int num_of_ones = 0;
  for (int i = 0; i < (int)digits_.size(); i++) {
    if (!condition && digits_[i]) {
      condition = true;
      nw_digits.push_back(digits_[i]);
    } else if (condition) {
      nw_digits.push_back(!digits_[i]);
    } else {
      nw_digits.push_back(digits_[i]);
    }
    if (digits_[i]) {
      ++num_of_ones;
    }
  }
  if (num_of_ones == (int)digits_.size()) {
    nw_digits.push_back(true);
  }
  BigInt<2> number_to_return;
  number_to_return.set_digits(nw_digits);
  return number_to_return;
}

/**
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline BigInt<2> BigInt<2>::operator*(const BigInt<2>& b) const {
  BigInt<2> c, d, e, f;
  if (*this == c || b == c) {
    return c;
  }
  e = b;
  if (b < d) {
    e = -b;
  }
  f = *this;
  if (f.digits()[f.digits().size() - 1]) {
    f = -f;
  }
  while (d != e) {
    c = c + f;
    e--;
  }
  f = *this;
  if (f.digits()[f.digits().size() - 1] != b.digits()[b.digits().size() - 1]) {
    c = -c;
  }
  return c;
}

/**
 * Sobrecarga del operador /
 * @brief Permite obtener el cociente dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline BigInt<2> operator/(const BigInt<2>& a, const BigInt<2>& b) {
  BigInt<2> c, d, e;
  if (b == c) {
    BigIntException exception;
    throw exception.BigIntDivisionByZero();
  }
  if (a == c) {
    return c;
  }
  c = a;
  if (a.digits()[a.digits().size() - 1]) {
    c = -c;
  }
  e = b;
  if (b.digits()[b.digits().size() - 1]) {
    e = -e;
  }
  while (c >= e) {
    c = c - e;
    ++d;
  }
  if (a.digits()[a.digits().size() - 1] != b.digits()[b.digits().size() - 1]) {
    d = -d;
  }
  return d;
}

/**
 * Sobrecarga del operador %
 * @brief Permite obtener el módulo dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline BigInt<2> BigInt<2>::operator%(const BigInt<2>& b) const {
  BigInt<2> c, d, e, f;
  bool condition = false;
  if (b == c) {
    BigIntException exception;
    throw exception.BigIntDivisionByZero();
  }
  if (*this == c) {
    return c;
  }
  c = *this;
  if (c.digits()[c.digits().size() - 1]) {
    c = -c;
  }
  e = b;
  if (b.digits()[b.digits().size() - 1]) {
    e = -e;
  }
  while (c >= e) {
    if (!condition) {
      condition = true;
    }
    c = c - e;
    ++d;
  }
  if (condition && (c != f)) {
    f = *this;
    if (f.digits()[f.digits().size() - 1]) {
      c = -c;
    }
  }
  return c;
}

/**
 * Power
 * @brief Permite elevar la potencia de un objeto de la clase BigInt elevado a otro objeto
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
inline BigInt<2> pow(const BigInt<2>& a, const BigInt<2>& b) {
  BigInt<2> c(1), d, e;
  if (b.digits()[b.digits().size() - 1]) {
    BigIntException exception;
    throw exception.BigIntIntegerRepresentation();
  }
  e = a;
  if (a.digits()[a.digits().size() - 1]) {
    e = -e;
  }
  while (d != b) {
    c = e * c;
    ++d;
  }
  if (a.digits()[a.digits().size() - 1]) {
    c = -c;
  }
  return c;
}

/**
 * Método Add
 * @brief Permite sumar dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
inline Number* BigInt<2>::add(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(this);
  if (p) {
    return new BigInt<2> (*this + static_cast<BigInt<2>>(*b));
  }
  return NULL;
}

/**
 * Método subtract
 * @brief Permite restar dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
inline Number* BigInt<2>::subtract(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(this);
  if (p) {
    return new BigInt<2> (*this - (BigInt<2>)*b);
  }
  return NULL;
}

/**
 * Método Multiply
 * @brief Permite multiplicar dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
inline Number* BigInt<2>::multiply(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(this);
  if (p) {
    return new BigInt<2> (*this * (BigInt<2>)*b);
  }
  return NULL;
}

/**
 * Método Divide
 * @brief Permite dividir dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
inline Number* BigInt<2>::divide(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(this);
  if (p) {
    return new BigInt<2> (*this / (BigInt<2>)*b);
  }
  return NULL;
}

/**
 * Método Module
 * @brief Permite obtener el módulo de dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
inline Number* BigInt<2>::module(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(this);
  if (p) {
    return new BigInt<2> (*this % (BigInt<2>)*b);
  }
  return NULL;
}

/**
 * Método Power
 * @brief Permite elevar a la potencia, dos objetos de la clase Number*
 * @param b : Objeto del tipo BigInt
 */
inline Number* BigInt<2>::power(const Number* b) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(this);
  if (p) {
    return new BigInt<2> (pow(*this, (BigInt<2>)*b));
  }
  return NULL;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto a base 2, dada cualquier tipo de base especificada
 */
template<size_t Base>
BigInt<Base>::operator BigInt<2>() const {
  BigInt<2> result;
  BigInt<Base> temp = *this, num_2(2), num_0; // Crea un objeto temporal de BigInt<Base> igual al objeto actual
  if (is_negative_) {
    temp = -temp;
  }
  std::vector<bool> binary_digits; // Vector para almacenar los dígitos binarios
  while (temp != num_0) {
    binary_digits.push_back((temp % num_2).digits_[0]); // Agrega el último dígito binario al vector
    temp = temp / num_2; // Divide entre 2 para continuar con la siguiente cifra binaria
  }
  if (binary_digits.empty()) {
    binary_digits.push_back(false); // Si el objeto original era cero, el resultado debe ser "0"
  }
  if (is_negative_) {
    binary_digits = compl_vector(binary_digits);
    binary_digits.push_back(true);
  } else {
    binary_digits.push_back(false);
  }
  result.set_digits(binary_digits);
  return result;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto a base 8, dada cualquier tipo de base especificada
 */
template<size_t Base>
BigInt<Base>::operator BigInt<8>() const {
  BigInt<8> result;
  BigInt<Base> temp = *this, num_8(8), num_0; // Crea un objeto temporal de BigInt<Base> igual al objeto actual
  std::vector<char> octal_digits; // Vector para almacenar los dígitos binarios
  while (temp != num_0) {
    octal_digits.push_back((temp % num_8).digits()[0]); // Agrega el último dígito binario al vector
    temp = temp / num_8; // Divide entre 2 para continuar con la siguiente cifra binaria
  }
  if (is_negative_) {
    result.set_is_negative(true);
  }
  result.set_digits(octal_digits);
  return result;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto a base 10, dada cualquier tipo de base especificada
 */
template<size_t Base>
BigInt<Base>::operator BigInt<10>() const {
  BigInt<10> zero_num;
  switch (Base) {
    case 8: {
      BigInt<8> actual_num = *this;
      BigInt<10> result;
      BigInt<10> base{1}, temp, number_base(8);
      for (char digit : actual_num.digits()) {
        if (digit != 0) {
          temp = temp + (base * (short)digit);
        }
        base = base * number_base;
      }
      result = temp;
      if (is_negative_) {
        result.set_is_negative(true);
      }
      return result;
    } case 16: {
      BigInt<16> actual_num = *this;
      BigInt<10> result;
      BigInt<10> base{1}, temp, number_base(16);
      for (char digit : actual_num.digits()) {
        if (digit != 0) {
          temp = temp + (base * (short)digit);
        }
        base = base * number_base;
      }
      result = temp;
      if (is_negative_) {
        result.set_is_negative(true);
      }
      return result;
    }
  }
  return zero_num;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto a base 16, dada cualquier tipo de base especificada
 */
template<size_t Base>
BigInt<Base>::operator BigInt<16>() const {
  BigInt<10> num = (BigInt<10>)*this;
  BigInt<16> result;
  BigInt<Base> temp = *this, num_16(16), num_0; // Crea un objeto temporal de BigInt<Base> igual al objeto actual
  std::vector<char> hex_digits; // Vector para almacenar los dígitos binarios
  while (temp != num_0) {
    hex_digits.push_back((temp % num_16).digits()[0]); // Agrega el último dígito binario al vector
    temp = temp / num_16; // Divide entre 2 para continuar con la siguiente cifra binaria
  }
  if (is_negative_) {
    result.set_is_negative(true);
  }
  result.set_digits(hex_digits);
  return result;
}

inline BigInt<2>::operator BigInt<2>() const {
  return *this;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 8, a base 2
 */
inline BigInt<2>::operator BigInt<8>() const {
  BigInt<8> result;
  BigInt<2> actual_num = *this;
  bool condition = false;
  if (digits()[digits().size() - 1]) {
    actual_num = -actual_num;
    condition = true;
  }
  std::vector<char> digits_octal;
  std::vector<bool> digits = actual_num.digits();
  int len = digits.size();
  if (len % 3 == 1) {
    digits.push_back(0);
    digits.push_back(0);
  } 
  if (len % 3 == 2) {
    digits.push_back(0);
  } 
  len = digits.size();
  for (int i = len - 1; i >= 0; i -= 3) {
    int octal = 0;
    octal += (digits[i] << 2);
    octal += (digits[i - 1] << 1);
    octal += (digits[i - 2]);
  }
  for (int i = digits_octal.size() - 1; i > 0; i--) {
    if ((short)digits_octal[i] == 0) {
      digits_octal.pop_back();
    } else {
      break;
    }
  }
  result.set_digits(digits_octal);
  if (condition) {
    result.set_is_negative(true);
  }
  return result;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 10, a base 2
 */
inline BigInt<2>::operator BigInt<10>() const {
  BigInt<2> actual_num = *this;
  BigInt<10> result;
  BigInt<10> base{1}, temp, dos(2);
  bool condition = false;
  if (digits()[digits().size() - 1]) {
    actual_num = -actual_num;
    condition = true;
  }
  for (bool digit : actual_num.digits()) {
    if (digit) {
      temp = temp + base;
    }
    base = base * dos;
  }
  result = temp;
  if (condition) {
    result.set_is_negative(true);
  }
  return result;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 16, a base 2
 */
inline BigInt<2>::operator BigInt<16>() const {
  BigInt<16> result;
  BigInt<2> actual_num = *this;
  bool condition = false;
  if (digits()[digits().size() - 1]) {
    actual_num = -actual_num;
    condition = true;
  }
  std::vector<char> digits_hex;
  std::vector<bool> digits = actual_num.digits();
  int len = digits.size();
  if (len % 4 == 1) {
    digits.push_back(false);
    digits.push_back(false);
    digits.push_back(false);
  }
  if (len % 4 == 2) {
    digits.push_back(false);
    digits.push_back(false);
  }
  if (len % 4 == 3) {
    digits.push_back(false);
  }
  len = digits.size();
  for (int i = len - 1; i > 0; i -= 4) {
    int hex = 0;
    hex += (digits[i] << 3);
    hex += (digits[i - 1] << 2);
    hex += (digits[i - 2] << 1);
    hex += digits[i - 3];
    digits_hex.insert(digits_hex.begin(), hex);
  }
  for (int i = digits_hex.size() - 1; i > 0; i--) {
    if ((short)digits_hex[i] == 0) {
      digits_hex.pop_back();
    } else {
      break;
    }
  }
  result.set_digits(digits_hex);
  if (condition) {
    result.set_is_negative(true);
  }
  return result;
}

/**
 * Método Create
 * @brief Método de la clase Number, que permite crear objetos de la clase BigInt
 * @param base : base del objeto a crear de la clase BigInt
 * @param s : string del nuevo número a inicializar de la clase BigInt
 */
inline Number* Number::create(size_t base, const std::string& s) {
  switch (base) {
    case 2: {
      return new BigInt<2> (s);
    } case 8: {
      return new BigInt<8> (s);
    } case 10: {
      return new BigInt<10> (s);
    } case 16: {
      return new BigInt<16> (s);
    } default: {
      BigIntException exception;
      throw exception.BigIntBaseNotImplemented();
    }
  }
  return NULL;
}