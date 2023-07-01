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
 * @file: bigint.h
 *    La clase BigInt nos permite operar y representar números enteros.
 */

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

template <>
class BigInt<8>;

template <>
class BigInt<10>;

template <>
class BigInt<16>;

/**
 * Especialización de plantilla par la clase BigInt<2> 
 * @brief Permite la representación de números grandes en 8 2
 */
template<>
class BigInt<2> : public Number {
 public: 
  /// Constructores
  BigInt(long n = 0);
  BigInt(std::string&);
  BigInt(const char*);
  BigInt(const BigInt<2>&); /// Constructor de copia
  /// Getter
  std::vector<bool> digits() const { return digits_; }
  /// Setter
  void set_digits(const std::vector<bool>& digits) { digits_ = digits; }
  /// Transformadores de 8
  operator BigInt<2>() const override; // código de conversión de binario a octal 
  operator BigInt<8>() const override; // código de conversión de binario a octal 
  operator BigInt<10>() const override; // código de conversión de binario a decimal 
  operator BigInt<16>() const override; // código de conversión de binario a hexadecimal 
  /// Asignación
  BigInt<2>& operator=(const BigInt<2>&);
  /// Inserción y extracción en flujo
  friend std::ostream& operator<<(std::ostream&, const Number&); 
  friend std::ostream& operator<<(std::ostream&, const BigInt<2>&); 
  friend std::istream& operator>>(std::istream&, BigInt<2>&);
  friend std::istream& operator>>(std::istream&, Number&);
  /// Accesor
  bool operator[](int) const; /// Acceso al i-ésimo dígito
  /// Comparación
  friend bool operator==(const BigInt<2>&, const BigInt<2> &); 
  bool operator!=(const BigInt<2>&) const;
  friend bool operator>(const BigInt<2>&, const BigInt<2> &); 
  bool operator>=(const BigInt<2> &) const;
  friend bool operator<(const BigInt<2>&, const BigInt<2>&); 
  bool operator<=(const BigInt<2>&) const;
  /// Incremento/decremento
  BigInt<2>& operator++(); /// Pre-incremento
  BigInt<2> operator++(int); /// Post-incremento
  BigInt<2>& operator--(); /// Pre-decremento
  BigInt<2> operator--(int); /// Pre-decremento 
  /// Operadores Aritméticos
  friend BigInt<2> operator+(const BigInt<2>&, const BigInt<2>&); 
  Number* add(const Number*) const override; 
  BigInt<2> operator-(const BigInt<2> &) const;
  Number* subtract(const Number*) const override;
  BigInt<2> operator-() const;
  BigInt<2> operator*(const BigInt<2>&) const;
  Number* multiply(const Number*) const override;
  Number* divide(const Number*) const override;
  Number* modulo(const Number*) const override;
  /// Potencia a^b
  Number* power(const Number*) const override;
 private:
  std::vector<bool> digits_;
  bool is_negative_;
};

/**
 * Complement Vector
 * @brief: Complementar un vector de bool, cuyo propósito es representar los dígitos de un número en 8 2, a complemento a 2.
 * @param digits_to_c2: dígitos de un número en 8 2, representación C2.
 */
std::vector<bool> compl_vector(const std::vector<bool>& digits_to_c2) {
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
 * Absolute Increase 8 2 
 * @brief: Permite incrementar un número en 8 2, de forma absoluta, dados sus dígitos en un vector de bool.
 * @param vector_of_digits: dígitos de un número en 8 2, representación C2.
 */
std::vector<bool> absolute_increase_2(const std::vector<bool>& vector_of_digits) {
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
 * Absolute Decrease 8 2 
 * @brief: Permite decrementar un número en 8 2, de forma absoluta, dados sus dígitos en un vector de bool.
 * @param vector_of_digits: dígitos de un número en 8 2, representación C2.
 */
std::vector<bool> absolute_decrease_2(const std::vector<bool>& vector_of_digits) {
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
 * Absolute Sum 8 2 
 * @brief: Permite sumar dos números en 8 2, de forma absoluta, dados sus dígitos en un vector de bool.
 * @param a: número en 8 2, representación C2.
 * @param b: número en 8 2, representación C2.
 */
BigInt<2> absolute_sum_2(const BigInt<2>& a, const BigInt<2>& b) {
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
BigInt<2>::BigInt(long n) {
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
BigInt<2>::BigInt(std::string& s) {
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
      throw std::invalid_argument("El número introducido no cumple los requisitos de la 8 especificada");
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
BigInt<2>::BigInt(const char* n) {
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
      throw std::invalid_argument("El número introducido no cumple los requisitos de la 8 especificada");
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
BigInt<2>::BigInt(const BigInt<2>& n) {
  digits_ = n.digits_;
}

/**
 * @brief Sobrecarga del operador de asignación de la clase BigInt<2>
 * @param n : Objeto del tipo BigInt
 */
BigInt<2>& BigInt<2>::operator=(const BigInt<2>& n) {
  digits_ = n.digits_;
  return *this;
}

/**
 * @brief Sobrecarga del operador de extracción de flujo de la clase BigInt
 * @param out : Objeto del tipo flujo estándar de salida
  * @param a : Objeto del tipo BigInt
 */
std::ostream& operator<<(std::ostream& out, const BigInt<2>& a) {
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
std::istream& operator>>(std::istream& in, BigInt<2>& a) {
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
      throw std::invalid_argument("El número introducido no cumple los requisitos de la 8 especificada");
    }
  }
  if (is_negative) {
    digits = compl_vector(digits);
  }
  a.set_digits(digits);
  return in;
}

/**
 * Sobrecarga del operador []
 * @brief Permite obtener el valor en el objeto en la posición indicada
 */
bool BigInt<2>::operator[](int i) const {
  assert(i >= 0 && i < (int)digits_.size());
  return digits_[i];
}

/**
 * Sobrecarga del operador ==
 * @brief Permite obtener si ambos objetos de la clase BigInt son iguales
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator==(const BigInt<2>& a, const BigInt<2> & b) {
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
bool BigInt<2>::operator!=(const BigInt<2>& b) const {
  return !(*this == b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es mayor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator>(const BigInt<2>& a, const BigInt<2> & b) {
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
bool BigInt<2>::operator>=(const BigInt<2> & b) const {
  return (*this == b || *this > b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator<(const BigInt<2>& a, const BigInt<2>& b) {
  return !(a >= b);
}

/**
 * Sobrecarga del operador >=
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor o igual que el segundo
 * @param b : Objeto del tipo BigInt
 */
bool BigInt<2>::operator<=(const BigInt<2>& b) const {
  return (*this == b || *this < b);
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
BigInt<2>& BigInt<2>::operator++() {
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
BigInt<2> BigInt<2>::operator++(int) {
  BigInt<2> temp(*this);
  ++(*this);
  return temp;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
BigInt<2>& BigInt<2>::operator--() {
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
BigInt<2> BigInt<2>::operator--(int) {
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
BigInt<2> operator+(const BigInt<2>& a, const BigInt<2>& b) {
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
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<2>::add(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(num);
  if (p) {
    BigInt<2> a = *this, b = *num, c, d, e;
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
    Number* number_final = new BigInt<2> (c);
    return number_final;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador -
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<2> BigInt<2>::operator-(const BigInt<2> &b) const {
  BigInt<2> c, d;
  d = -b;
  c = *this + d;
  return c;
}

/**
 * Sobrecarga del operador -
 * @brief Permite cambiar el signo del objeto invocante
 */
BigInt<2> BigInt<2>::operator-() const {
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
 * Sobrecarga del operador -
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<2>::subtract(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(num);
  if (p) {
    BigInt<2> b = *num, c = *this, d;
    d = -b;
    c = c + d;
    Number* number_final = new BigInt<2> (c);
    return number_final;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<2> BigInt<2>::operator*(const BigInt<2>& b) const {
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
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<2>::multiply(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(num);
  if (p) {
    BigInt<2> a = *this, b = *num, c, d, e, f;
    if (*this == c || b == c) {
      Number* number_final = new BigInt<2> (c);
      return number_final;
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
    Number* number_final = new BigInt<2> (c);
    return number_final;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador /
 * @brief Permite obtener el cociente dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<2>::divide(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(num);
  if (p) {
    BigInt<2> a = *this, b = *num, c, d, e;
    if (b == c) {
      throw std::invalid_argument("Division por cero");
    }
    if (a == c) {
      Number* number_final = new BigInt<2> (c);
      return number_final;
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
    Number* number_final = new BigInt<2> (d);
    return number_final;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador %
 * @brief Permite obtener el módulo dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<2>::modulo(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(num);
  if (p) { 
    BigInt<2> a = *this, b = *num, c, d, e, f;
    bool condition = false;
    if (b == c) {
      throw std::invalid_argument("Division por cero");
    }
    if (*this == c) {
      Number* number_final = new BigInt<2> (c);
      return number_final;
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
    Number* number_final = new BigInt<2> (c);
    return number_final;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Power
 * @brief Permite elevar la potencia de un objeto de la clase BigInt elevado a otro objeto
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<2>::power(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<2>*>(num);
  if (p) { 
    BigInt<2> a = *this, b = *num, c(1), d, e;
    if (b.digits()[b.digits().size() - 1]) {
      throw std::invalid_argument("Representación entera!");
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
    Number* number_final = new BigInt<2> (c);
    return number_final;
  } else {
    throw "Referencia a puntero inválida!";
  }
}


/**
 * Clase BigInt
 * @brief Permite la representación de números grandes
 */
template<>
class BigInt<8> : public Number {
 public:
  /// Constructores
  BigInt(long n = 0);
  BigInt(std::string&);
  BigInt(const char*);
  BigInt(const BigInt<8>&); /// Constructor de copia
  /// Transformador de 8
  operator BigInt<2>() const override;
  operator BigInt<8>() const override;
  operator BigInt<10>() const override;
  operator BigInt<16>() const override;
  /// Asignación
  BigInt<8>& operator=(const BigInt<8>&);
  /// Inserción y extracción en flujo
  friend std::ostream& operator<<(std::ostream&, const Number&);
  friend std::ostream& operator<<(std::ostream&, const BigInt<8>&); 
  friend std::istream& operator>>(std::istream&, Number&);
  friend std::istream& operator>>(std::istream&, BigInt<8>&);
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
  friend bool operator==(const BigInt<8>&, const BigInt<8>&); 
  bool operator!=(const BigInt<8>&) const;
  friend bool operator>(const BigInt<8>&, const BigInt<8> &); 
  bool operator>=(const BigInt<8> &) const;
  friend bool operator<(const BigInt<8>&, const BigInt<8>&); 
  bool operator<=(const BigInt<8>&) const;
  /// Incremento/decremento
  BigInt<8>& operator++(); /// Pre-incremento
  BigInt<8> operator++(int); /// Post-incremento
  BigInt<8>& operator--(); /// Pre-decremento
  BigInt<8> operator--(int); /// Pre-decremento 
  /// Operadores Aritméticos
  friend BigInt<8> operator+(const BigInt<8>&, const BigInt<8>&); 
  Number* add(const Number*) const override; 
  BigInt<8> operator-(const BigInt<8> &) const;
  Number* subtract(const Number*) const override;
  BigInt<8> operator-() const;
  BigInt<8> operator*(const BigInt<8>&) const;
  Number* multiply(const Number*) const override;
  Number* divide(const Number*) const override; 
  Number* modulo(const Number*) const override;
  /// Potencia a^b
  Number* power(const Number*) const override;
  /// Otros
  friend BigInt<8> absolute_sum(const BigInt<8>&, const BigInt<8>&);
  friend BigInt<8> absolute_substraction(const BigInt<8>&, const BigInt<8>&);
  friend bool absolute_value(const BigInt<8>&, const BigInt<8>&);
 private:
  std::vector<char> digits_;
  bool is_negative_ = false;
};

/**
 * Absolute increase
 * @brief Permite incrementar un número de forma absoluta
 * @param digits_ : vector de dígitos
 * @param 8 : 8 del número en cuestión
 */
std::vector<char> absolute_increase(const std::vector<char>& digits_, size_t base = 8) {
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
 * @param 8 : 8 del número en cuestión
 */
std::vector<char> absolute_decrease(const std::vector<char>& digits_, size_t base = 8) {
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
BigInt<8> absolute_sum(const BigInt<8>& a, const BigInt<8>& b) {
  BigInt<8> c;
  std::vector<char> c_vector;
  int carry = 0;
  int size_a = a.digits().size();
  int size_b = b.digits().size();
  for (int i = 0; i < std::max(size_a, size_b); i++) {
    int d1 = (i < size_a) ? a.digits()[i] : 0;
    int d2 = (i < size_b) ? b.digits()[i] : 0;
    c_vector.push_back((d1 + d2 + carry) % 8);
    carry = (d1 + d2 + carry) / 8;
  }
  if (carry) {
    c_vector.push_back(carry);
  }
  c.set_digits(c_vector);
  return c;
}

/**
 * Absolute substraction
 * @brief Permite la resta de dos números de forma absoluta
 * @param a : minuendo
 * @param b : sustraendo
 */
BigInt<8> absolute_substraction(const BigInt<8>& a, const BigInt<8>& b)  {
  BigInt<8> c;
  std::vector<char> c_vector;
  int carry = 0;
  int size_a = a.digits().size();
  int size_b = b.digits().size();
  for (int i = 0; i < size_b; i++) {
    int d1 = a.digits()[i];
    int d2 = b.digits()[i];
    if (d1 - carry < d2) {
      c_vector.push_back((short)((d1 + 8 - carry) - d2));
      carry = 1;
    } else {
      c_vector.push_back(d1 - carry - d2);
      carry = 0;
    }
  }
  for (int i = size_b; i < size_a; i++) {
    int d1 = a.digits()[i];
    if (d1 - carry < 0) { 
      c_vector.push_back(d1 + 8 - carry);
      carry = 1;
    } else {
      c_vector.push_back(d1 - carry);
      carry = 0;
    }
  }
  while (c_vector.size() > 1 && (short)c_vector.back() == 0) {
    c_vector.pop_back();
  }
  c.set_digits(c_vector);
  return c;
}

/**
 * Absolute Value >
 * @brief Nos permite comparar números de forma absoluta para determinar su el primer número es mayor que el segundo
 * @param a : primer número de la clase BigInt
 * @param b : segundo número de la clase BigInt
 */
bool absolute_value(const BigInt<8>& a, const BigInt<8>& b) {
  if (a.digits().size() > b.digits().size()) {
    return true;
  } else if (a.digits().size() < b.digits().size()) {
    return false;
  }
  for (int i = a.digits().size() - 1; i >= 0; i--) {
    if (a[i] != b[i]) {
      if (a[i] > b[i]) {
        return true;
      } else {
        return false;
      }
    }
  }
  if (std::max(a.digits().size(), b.digits().size()) == a.digits().size()) {
    return true;
  }
  return false;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo long
 * @param long : Objeto del tipo long
 */
BigInt<8>::BigInt(long n) {
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  if (n < 0) {
    is_negative_ = true;
    n = -n;
  }
  do {
    digits.push_back(n % 8);
    n /= 8;
  } while (n > 0);
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para cadenas
 * @param s : Objeto del tipo string
 */
BigInt<8>::BigInt(std::string& s) {
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
  s = aux;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] >= 'A') {
      digits.push_back(s[i] - 'A' + 10);
    } else {
      digits.push_back(s[i] - '0');
    }
  }
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo char* (array de char)
 * @param n : Objeto del tipo char*
 */
BigInt<8>::BigInt(const char* n) {
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
BigInt<8>::BigInt(const BigInt<8>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
}

/**
 * @brief Sobrecarga del operador de asignación de la clase BigInt
 * @param n : Objeto del tipo BigInt
 */
BigInt<8>& BigInt<8>::operator=(const BigInt<8>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
  return *this;
}

/**
 * @brief Sobrecarga del operador de extracción de flujo de la clase BigInt
 * @param out : Objeto del tipo flujo estándar de salida
  * @param a : Objeto del tipo BigInt
 */
std::ostream& operator<<(std::ostream& out, const BigInt<8>&a) {
  if (a.is_negative_) {
    out << "-";
  }
  for (int i = a.digits_.size() - 1; i >= 0; i--) {
    if ((short)a.digits_[i] < 10) {
      out << (char)('0' + a.digits_[i]);
    } else {
      out << (char)('A' + a.digits_[i] - 10);
    }
  }
  return out;
}

/**
 * @brief Sobrecarga del operador de inserción de flujo de la clase BigInt
 * @param in : Objeto del tipo flujo estándar de entrada
 * @param a : Objeto del tipo BigInt
 */
std::istream& operator>>(std::istream& in, BigInt<8>& a) {
  std::string s;
  in >> s;
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  int j = 0;
  if (s[0] == '-') {
    a.is_negative_ = true;
    ++j;
  }
  for (int i = s.size() - 1; i >= j; i--) {
    if (s[i] >= 'A') {
      digits.push_back(10 + s[i] - '0');
    } else {
      digits.push_back(s[i] - '0');
    }
  }
  a.digits_ = digits;
  return in;
}

/**
 * Sign
 * @brief Permite saber el síngo del objeto invocante
 */
int BigInt<8>::sign() const {
  return (is_negative_ ? -1 : 1);
}

/**
 * Sobrecarga del operador []
 * @brief Permite obtener el valor en el objeto en la posición indicada
 */
char BigInt<8>::operator[](int i) const {
  assert(i >= 0 && i < (int)digits_.size());
  return digits_[i];
}

/**
 * Sobrecarga del operador ==
 * @brief Permite obtener si ambos objetos de la clase BigInt son iguales
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator==(const BigInt<8>& a, const BigInt<8> & b) {
  if ((a.is_negative() != b.is_negative()) || (a.digits().size() != b.digits().size())) {
    return false;
  }
  for (size_t i = 0; i < a.digits().size(); i++) {
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
bool BigInt<8>::operator!=(const BigInt<8>& b) const {
  return !(*this == b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es mayor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator>(const BigInt<8>& a, const BigInt<8> & b) {
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
bool BigInt<8>::operator>=(const BigInt<8> & b) const {
  return (*this == b || *this > b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator<(const BigInt<8>& a, const BigInt<8>& b) {
  return !(a >= b);
}

/**
 * Sobrecarga del operador >=
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor o igual que el segundo
 * @param b : Objeto del tipo BigInt
 */
bool BigInt<8>::operator<=(const BigInt<8>& b) const {
  return (*this == b || *this < b);
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
BigInt<8>& BigInt<8>::operator++() {
  std::vector<char> &digits = this->digits_;
  if (is_negative_ == true) {
    digits = absolute_decrease(digits_, 8);
    // Declaración de "-0"
    BigInt<8> n1;
    n1 = -n1;
    if (n1 == *this) {
      is_negative_ = false;
    }
  } else {
    digits = absolute_increase(digits_, 8);
  }
  return *this;
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
BigInt<8> BigInt<8>::operator++(int) {
  BigInt<8> temp(*this);
  ++(*this);
  return temp;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
BigInt<8>& BigInt<8>::operator--() {
  std::vector<char> &digits = this->digits_;
  if (is_negative_ == false) {
    digits = absolute_decrease(digits_, 8);
  } else {
    digits = absolute_increase(digits_, 8);
  }
  return *this;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
BigInt<8> BigInt<8>::operator--(int) {
  BigInt<8> temp(*this);
  --(*this);
  return temp;
}

/**
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<8> operator+(const BigInt<8>& a, const BigInt<8>& b) {
  BigInt<8> c;
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
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<8>::add(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<8>*>(num);
  if (p) {
    BigInt<8> a = *this, b = *num, c;
    if (a == c || b == c) {
      if (a == c) {
        Number* final_number = new BigInt<8> (b);
        return final_number;
      } else {
        Number* final_number = new BigInt<8> (a);
        return final_number;
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
    Number* final_number = new BigInt<8> (c);
    return final_number;
  } else {
    throw "Referencia de puntero inválida!";
  }
}

/**
 * Sobrecarga del operador -
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<8> BigInt<8>::operator-(const BigInt<8> &b) const {
  BigInt<8> c;
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
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<8>::subtract(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<8>*>(num);
  if (p) {
    BigInt<8> a = *this, b = *num, c;
    if (*this == c || b == c) {
      if (*this == c) {
        c = -b;
      } else {
        c = -*this;
      }
      Number* final_number = new BigInt<8> (c);
      return final_number;
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
    Number* final_number = new BigInt<8> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador -
 * @brief Permite cambiar el signo del objeto invocante
 */
BigInt<8> BigInt<8>::operator-() const {
  bool condition = !(is_negative_);
  BigInt<8> n = *this;
  n.is_negative_ = condition;
  return n;
}

/**
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<8> BigInt<8>::operator*(const BigInt<8>& b) const {
  BigInt<8> c, d, e;
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
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<8>::multiply(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<8>*>(num);
  if (p) {  
    BigInt<8> a = *this, b = *num, c, d, e;
    bool cond_sum = false;
    if (*this == c || b == c) {
      Number* final_number = new BigInt<8> (c);
      return final_number;
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
    Number* final_number = new BigInt<8> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador /
 * @brief Permite obtener el cociente dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<8>::divide(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<8>*>(num);
  if (p) {  
    BigInt<8> a = *this, b = *num, c, d, e;
    if (b == c) {
      throw std::invalid_argument("Division por cero");
    }
    if (a == c) {
      Number* final_number = new BigInt<8> (c);
      return final_number;
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
    Number* final_number = new BigInt<8> (e);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador %
 * @brief Permite obtener el módulo dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<8>::modulo(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<8>*>(num);
  if (p) {  
    BigInt<8> a = *this, b = *num, c, d, e, f;
    if (b == c) {
      throw std::invalid_argument("Division por cero");
    }
    if (*this == c) {
      Number* final_number = new BigInt<8> (c);
      return final_number;
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
    Number* final_number = new BigInt<8> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Power
 * @brief Permite elevar la potencia de un objeto de la clase BigInt elevado a otro objeto
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<8>::power(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<8>*>(num);
  if (p) {  
    BigInt<8> a = *this, b = *num, c(1), d;
    if (b.is_negative_) {
      throw std::invalid_argument("Representación entera!");
    }
    while (d < b) {
      c = a * c;
      ++d;
    }
    Number* final_number = new BigInt<8> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Clase BigInt
 * @brief Permite la representación de números grandes
 */
template<>
class BigInt<10> : public Number {
 public:
  /// Constructores
  BigInt(long n = 0);
  BigInt(std::string&);
  BigInt(const char*);
  BigInt(const BigInt<10>&); /// Constructor de copia
  /// Transformador de 10
  operator BigInt<2>() const override;
  operator BigInt<8>() const override;
  operator BigInt<10>() const override;
  operator BigInt<16>() const override;
  /// Asignación
  BigInt<10>& operator=(const BigInt<10>&);
  /// Inserción y extracción en flujo
  friend std::ostream& operator<<(std::ostream&, const Number&);
  friend std::ostream& operator<<(std::ostream&, const BigInt<10>&); 
  friend std::istream& operator>>(std::istream&, Number&);
  friend std::istream& operator>>(std::istream&, BigInt<10>&);
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
  friend bool operator==(const BigInt<10>&, const BigInt<10>&); 
  bool operator!=(const BigInt<10>&) const;
  friend bool operator>(const BigInt<10>&, const BigInt<10> &); 
  bool operator>=(const BigInt<10> &) const;
  friend bool operator<(const BigInt<10>&, const BigInt<10>&); 
  bool operator<=(const BigInt<10>&) const;
  /// Incremento/decremento
  BigInt<10>& operator++(); /// Pre-incremento
  BigInt<10> operator++(int); /// Post-incremento
  BigInt<10>& operator--(); /// Pre-decremento
  BigInt<10> operator--(int); /// Pre-decremento 
  /// Operadores Aritméticos
  friend BigInt<10> operator+(const BigInt<10>&, const BigInt<10>&); 
  Number* add(const Number*) const override; 
  BigInt<10> operator-(const BigInt<10> &) const;
  Number* subtract(const Number*) const override;
  BigInt<10> operator-() const;
  BigInt<10> operator*(const BigInt<10>&) const;
  Number* multiply(const Number*) const override;
  Number* divide(const Number*) const override; 
  Number* modulo(const Number*) const override;
  /// Potencia a^b
  Number* power(const Number*) const override;
  /// Otros
  friend BigInt<10> absolute_sum(const BigInt<10>&, const BigInt<10>&);
  friend BigInt<10> absolute_substraction(const BigInt<10>&, const BigInt<10>&);
  friend bool absolute_value(const BigInt<10>&, const BigInt<10>&);
 private:
  std::vector<char> digits_;
  bool is_negative_ = false;
};

/**
 * Absolute sum
 * @brief Permite la suma de dos números de forma absoluta
 * @param a : primer sumando
 * @param b : segundo sumando
 */
BigInt<10> absolute_sum(const BigInt<10>& a, const BigInt<10>& b) {
  BigInt<10> c;
  std::vector<char> c_vector;
  int carry = 0;
  int size_a = a.digits().size();
  int size_b = b.digits().size();
  for (int i = 0; i < std::max(size_a, size_b); i++) {
    int d1 = (i < size_a) ? a.digits()[i] : 0;
    int d2 = (i < size_b) ? b.digits()[i] : 0;
    c_vector.push_back((d1 + d2 + carry) % 10);
    carry = (d1 + d2 + carry) / 10;
  }
  if (carry) {
    c_vector.push_back(carry);
  }
  c.set_digits(c_vector);
  return c;
}

/**
 * Absolute substraction
 * @brief Permite la resta de dos números de forma absoluta
 * @param a : minuendo
 * @param b : sustraendo
 */
BigInt<10> absolute_substraction(const BigInt<10>& a, const BigInt<10>& b)  {
  BigInt<10> c;
  std::vector<char> c_vector;
  int carry = 0;
  int size_a = a.digits().size();
  int size_b = b.digits().size();
  for (int i = 0; i < size_b; i++) {
    int d1 = a.digits()[i];
    int d2 = b.digits()[i];
    if (d1 - carry < d2) {
      c_vector.push_back((short)((d1 + 10 - carry) - d2));
      carry = 1;
    } else {
      c_vector.push_back(d1 - carry - d2);
      carry = 0;
    }
  }
  for (int i = size_b; i < size_a; i++) {
    int d1 = a.digits()[i];
    if (d1 - carry < 0) { 
      c_vector.push_back(d1 + 10 - carry);
      carry = 1;
    } else {
      c_vector.push_back(d1 - carry);
      carry = 0;
    }
  }
  while (c_vector.size() > 1 && (short)c_vector.back() == 0) {
    c_vector.pop_back();
  }
  c.set_digits(c_vector);
  return c;
}

/**
 * Absolute Value >
 * @brief Nos permite comparar números de forma absoluta para determinar su el primer número es mayor que el segundo
 * @param a : primer número de la clase BigInt
 * @param b : segundo número de la clase BigInt
 */
bool absolute_value(const BigInt<10>& a, const BigInt<10>& b) {
  if (a.digits().size() > b.digits().size()) {
    return true;
  } else if (a.digits().size() < b.digits().size()) {
    return false;
  }
  for (int i = a.digits().size() - 1; i >= 0; i--) {
    if (a[i] != b[i]) {
      if (a[i] > b[i]) {
        return true;
      } else {
        return false;
      }
    }
  }
  if (std::max(a.digits().size(), b.digits().size()) == a.digits().size()) {
    return true;
  }
  return false;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo long
 * @param long : Objeto del tipo long
 */
BigInt<10>::BigInt(long n) {
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  if (n < 0) {
    is_negative_ = true;
    n = -n;
  }
  do {
    digits.push_back(n % 10);
    n /= 10;
  } while (n > 0);
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para cadenas
 * @param s : Objeto del tipo string
 */
BigInt<10>::BigInt(std::string& s) {
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
  s = aux;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] >= 'A') {
      digits.push_back(s[i] - 'A' + 10);
    } else {
      digits.push_back(s[i] - '0');
    }
  }
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo char* (array de char)
 * @param n : Objeto del tipo char*
 */
BigInt<10>::BigInt(const char* n) {
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
BigInt<10>::BigInt(const BigInt<10>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
}

/**
 * @brief Sobrecarga del operador de asignación de la clase BigInt
 * @param n : Objeto del tipo BigInt
 */
BigInt<10>& BigInt<10>::operator=(const BigInt<10>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
  return *this;
}

/**
 * @brief Sobrecarga del operador de extracción de flujo de la clase BigInt
 * @param out : Objeto del tipo flujo estándar de salida
  * @param a : Objeto del tipo BigInt
 */
std::ostream& operator<<(std::ostream& out, const BigInt<10>&a) {
  if (a.is_negative_) {
    out << "-";
  }
  for (int i = a.digits_.size() - 1; i >= 0; i--) {
    if ((short)a.digits_[i] < 10) {
      out << (char)('0' + a.digits_[i]);
    } else {
      out << (char)('A' + a.digits_[i] - 10);
    }
  }
  return out;
}

/**
 * @brief Sobrecarga del operador de inserción de flujo de la clase BigInt
 * @param in : Objeto del tipo flujo estándar de entrada
 * @param a : Objeto del tipo BigInt
 */
std::istream& operator>>(std::istream& in, BigInt<10>& a) {
  std::string s;
  in >> s;
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  int j = 0;
  if (s[0] == '-') {
    a.is_negative_ = true;
    ++j;
  }
  for (int i = s.size() - 1; i >= j; i--) {
    if (s[i] >= 'A') {
      digits.push_back(10 + s[i] - '0');
    } else {
      digits.push_back(s[i] - '0');
    }
  }
  a.digits_ = digits;
  return in;
}

/**
 * Sign
 * @brief Permite saber el síngo del objeto invocante
 */
int BigInt<10>::sign() const {
  return (is_negative_ ? -1 : 1);
}

/**
 * Sobrecarga del operador []
 * @brief Permite obtener el valor en el objeto en la posición indicada
 */
char BigInt<10>::operator[](int i) const {
  assert(i >= 0 && i < (int)digits_.size());
  return digits_[i];
}

/**
 * Sobrecarga del operador ==
 * @brief Permite obtener si ambos objetos de la clase BigInt son iguales
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator==(const BigInt<10>& a, const BigInt<10> & b) {
  if ((a.is_negative() != b.is_negative()) || (a.digits().size() != b.digits().size())) {
    return false;
  }
  for (size_t i = 0; i < a.digits().size(); i++) {
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
bool BigInt<10>::operator!=(const BigInt<10>& b) const {
  return !(*this == b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es mayor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator>(const BigInt<10>& a, const BigInt<10> & b) {
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
bool BigInt<10>::operator>=(const BigInt<10> & b) const {
  return (*this == b || *this > b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator<(const BigInt<10>& a, const BigInt<10>& b) {
  return !(a >= b);
}

/**
 * Sobrecarga del operador >=
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor o igual que el segundo
 * @param b : Objeto del tipo BigInt
 */
bool BigInt<10>::operator<=(const BigInt<10>& b) const {
  return (*this == b || *this < b);
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
BigInt<10>& BigInt<10>::operator++() {
  std::vector<char> &digits = this->digits_;
  if (is_negative_ == true) {
    digits = absolute_decrease(digits_, 10);
    // Declaración de "-0"
    BigInt<10> n1;
    n1 = -n1;
    if (n1 == *this) {
      is_negative_ = false;
    }
  } else {
    digits = absolute_increase(digits_, 10);
  }
  return *this;
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
BigInt<10> BigInt<10>::operator++(int) {
  BigInt<10> temp(*this);
  ++(*this);
  return temp;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
BigInt<10>& BigInt<10>::operator--() {
  std::vector<char> &digits = this->digits_;
  if (is_negative_ == false) {
    digits = absolute_decrease(digits_, 10);
  } else {
    digits = absolute_increase(digits_, 10);
  }
  return *this;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
BigInt<10> BigInt<10>::operator--(int) {
  BigInt<10> temp(*this);
  --(*this);
  return temp;
}

/**
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<10> operator+(const BigInt<10>& a, const BigInt<10>& b) {
  BigInt<10> c;
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
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<10>::add(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<10>*>(num);
  if (p) {
    BigInt<10> a = *this, b = *num, c;
    if (a == c || b == c) {
      if (a == c) {
        Number* final_number = new BigInt<10> (b);
        return final_number;
      } else {
        Number* final_number = new BigInt<10> (a);
        return final_number;
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
    Number* final_number = new BigInt<10> (c);
    return final_number;
  } else {
    throw "Referencia de puntero inválida!";
  }
}

/**
 * Sobrecarga del operador -
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<10> BigInt<10>::operator-(const BigInt<10> &b) const {
  BigInt<10> c;
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
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<10>::subtract(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<10>*>(num);
  if (p) {
    BigInt<10> a = *this, b = *num, c;
    if (*this == c || b == c) {
      if (*this == c) {
        c = -b;
      } else {
        c = -*this;
      }
      Number* final_number = new BigInt<10> (c);
      return final_number;
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
    Number* final_number = new BigInt<10> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador -
 * @brief Permite cambiar el signo del objeto invocante
 */
BigInt<10> BigInt<10>::operator-() const {
  bool condition = !(is_negative_);
  BigInt<10> n = *this;
  n.is_negative_ = condition;
  return n;
}

/**
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<10> BigInt<10>::operator*(const BigInt<10>& b) const {
  BigInt<10> c, d, e;
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
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<10>::multiply(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<10>*>(num);
  if (p) {  
    BigInt<10> a = *this, b = *num, c, d, e;
    bool cond_sum = false;
    if (*this == c || b == c) {
      Number* final_number = new BigInt<10> (c);
      return final_number;
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
    Number* final_number = new BigInt<10> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador /
 * @brief Permite obtener el cociente dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<10>::divide(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<10>*>(num);
  if (p) {  
    BigInt<10> a = *this, b = *num, c, d, e;
    if (b == c) {
      throw std::invalid_argument("Division por cero");
    }
    if (a == c) {
      Number* final_number = new BigInt<10> (c);
      return final_number;
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
    Number* final_number = new BigInt<10> (e);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador %
 * @brief Permite obtener el módulo dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<10>::modulo(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<10>*>(num);
  if (p) {  
    BigInt<10> a = *this, b = *num, c, d, e, f;
    if (b == c) {
      throw std::invalid_argument("Division por cero");
    }
    if (*this == c) {
      Number* final_number = new BigInt<10> (c);
      return final_number;
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
    Number* final_number = new BigInt<10> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Power
 * @brief Permite elevar la potencia de un objeto de la clase BigInt elevado a otro objeto
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<10>::power(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<10>*>(num);
  if (p) {  
    BigInt<10> a = *this, b = *num, c(1), d;
    if (b.is_negative_) {
      throw std::invalid_argument("Representación entera!");
    }
    while (d < b) {
      c = a * c;
      ++d;
    }
    Number* final_number = new BigInt<10> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}


/**
 * Clase BigInt
 * @brief Permite la representación de números grandes
 */
template<>
class BigInt<16> : public Number {
 public:
  /// Constructores
  BigInt(long n = 0);
  BigInt(std::string&);
  BigInt(const char*);
  BigInt(const BigInt<16>&); /// Constructor de copia
  /// Transformador de 16
  operator BigInt<2>() const override;
  operator BigInt<8>() const override;
  operator BigInt<10>() const override;
  operator BigInt<16>() const override;
  /// Asignación
  BigInt<16>& operator=(const BigInt<16>&);
  /// Inserción y extracción en flujo
  friend std::ostream& operator<<(std::ostream&, const Number&);
  friend std::ostream& operator<<(std::ostream&, const BigInt<16>&); 
  friend std::istream& operator>>(std::istream&, Number&);
  friend std::istream& operator>>(std::istream&, BigInt<16>&);
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
  friend bool operator==(const BigInt<16>&, const BigInt<16>&); 
  bool operator!=(const BigInt<16>&) const;
  friend bool operator>(const BigInt<16>&, const BigInt<16> &); 
  bool operator>=(const BigInt<16> &) const;
  friend bool operator<(const BigInt<16>&, const BigInt<16>&); 
  bool operator<=(const BigInt<16>&) const;
  /// Incremento/decremento
  BigInt<16>& operator++(); /// Pre-incremento
  BigInt<16> operator++(int); /// Post-incremento
  BigInt<16>& operator--(); /// Pre-decremento
  BigInt<16> operator--(int); /// Pre-decremento 
  /// Operadores Aritméticos
  friend BigInt<16> operator+(const BigInt<16>&, const BigInt<16>&); 
  Number* add(const Number*) const override; 
  BigInt<16> operator-(const BigInt<16> &) const;
  Number* subtract(const Number*) const override;
  BigInt<16> operator-() const;
  BigInt<16> operator*(const BigInt<16>&) const;
  Number* multiply(const Number*) const override;
  Number* divide(const Number*) const override; 
  Number* modulo(const Number*) const override;
  /// Potencia a^b
  Number* power(const Number*) const override;
  /// Otros
  friend BigInt<16> absolute_sum(const BigInt<16>&, const BigInt<16>&);
  friend BigInt<16> absolute_substraction(const BigInt<16>&, const BigInt<16>&);
  friend bool absolute_value(const BigInt<16>&, const BigInt<16>&);
 private:
  std::vector<char> digits_;
  bool is_negative_ = false;
};

/**
 * Absolute sum
 * @brief Permite la suma de dos números de forma absoluta
 * @param a : primer sumando
 * @param b : segundo sumando
 */
BigInt<16> absolute_sum(const BigInt<16>& a, const BigInt<16>& b) {
  BigInt<16> c;
  std::vector<char> c_vector;
  int carry = 0;
  int size_a = a.digits().size();
  int size_b = b.digits().size();
  for (int i = 0; i < std::max(size_a, size_b); i++) {
    int d1 = (i < size_a) ? a.digits()[i] : 0;
    int d2 = (i < size_b) ? b.digits()[i] : 0;
    c_vector.push_back((d1 + d2 + carry) % 16);
    carry = (d1 + d2 + carry) / 16;
  }
  if (carry) {
    c_vector.push_back(carry);
  }
  c.set_digits(c_vector);
  return c;
}

/**
 * Absolute substraction
 * @brief Permite la resta de dos números de forma absoluta
 * @param a : minuendo
 * @param b : sustraendo
 */
BigInt<16> absolute_substraction(const BigInt<16>& a, const BigInt<16>& b)  {
  BigInt<16> c;
  std::vector<char> c_vector;
  int carry = 0;
  int size_a = a.digits().size();
  int size_b = b.digits().size();
  for (int i = 0; i < size_b; i++) {
    int d1 = a.digits()[i];
    int d2 = b.digits()[i];
    if (d1 - carry < d2) {
      c_vector.push_back((short)((d1 + 16 - carry) - d2));
      carry = 1;
    } else {
      c_vector.push_back(d1 - carry - d2);
      carry = 0;
    }
  }
  for (int i = size_b; i < size_a; i++) {
    int d1 = a.digits()[i];
    if (d1 - carry < 0) { 
      c_vector.push_back(d1 + 16 - carry);
      carry = 1;
    } else {
      c_vector.push_back(d1 - carry);
      carry = 0;
    }
  }
  while (c_vector.size() > 1 && (short)c_vector.back() == 0) {
    c_vector.pop_back();
  }
  c.set_digits(c_vector);
  return c;
}

/**
 * Absolute Value >
 * @brief Nos permite comparar números de forma absoluta para determinar su el primer número es mayor que el segundo
 * @param a : primer número de la clase BigInt
 * @param b : segundo número de la clase BigInt
 */
bool absolute_value(const BigInt<16>& a, const BigInt<16>& b) {
  if (a.digits().size() > b.digits().size()) {
    return true;
  } else if (a.digits().size() < b.digits().size()) {
    return false;
  }
  for (int i = a.digits().size() - 1; i >= 0; i--) {
    if (a[i] != b[i]) {
      if (a[i] > b[i]) {
        return true;
      } else {
        return false;
      }
    }
  }
  if (std::max(a.digits().size(), b.digits().size()) == a.digits().size()) {
    return true;
  }
  return false;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo long
 * @param long : Objeto del tipo long
 */
BigInt<16>::BigInt(long n) {
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  if (n < 0) {
    is_negative_ = true;
    n = -n;
  }
  do {
    digits.push_back(n % 16);
    n /= 16;
  } while (n > 0);
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para cadenas
 * @param s : Objeto del tipo string
 */
BigInt<16>::BigInt(std::string& s) {
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
  s = aux;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] >= 'A') {
      digits.push_back(s[i] - 'A' + 16);
    } else {
      digits.push_back(s[i] - '0');
    }
  }
  digits_ = digits;
}

/**
 * @brief Constructor de la clase BigInt para números del tipo char* (array de char)
 * @param n : Objeto del tipo char*
 */
BigInt<16>::BigInt(const char* n) {
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
      digits.push_back(n[i] - 'A' + 16);
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
BigInt<16>::BigInt(const BigInt<16>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
}

/**
 * @brief Sobrecarga del operador de asignación de la clase BigInt
 * @param n : Objeto del tipo BigInt
 */
BigInt<16>& BigInt<16>::operator=(const BigInt<16>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
  return *this;
}

/**
 * @brief Sobrecarga del operador de extracción de flujo de la clase BigInt
 * @param out : Objeto del tipo flujo estándar de salida
  * @param a : Objeto del tipo BigInt
 */
std::ostream& operator<<(std::ostream& out, const BigInt<16>&a) {
  if (a.is_negative_) {
    out << "-";
  }
  for (int i = a.digits_.size() - 1; i >= 0; i--) {
    if ((short)a.digits_[i] < 16) {
      out << (char)('0' + a.digits_[i]);
    } else {
      out << (char)('A' + a.digits_[i] - 16);
    }
  }
  return out;
}

/**
 * @brief Sobrecarga del operador de inserción de flujo de la clase BigInt
 * @param in : Objeto del tipo flujo estándar de entrada
 * @param a : Objeto del tipo BigInt
 */
std::istream& operator>>(std::istream& in, BigInt<16>& a) {
  std::string s;
  in >> s;
  std::vector<char> digits;
  /// Comprobar si el número es negativo
  int j = 0;
  if (s[0] == '-') {
    a.is_negative_ = true;
    ++j;
  }
  for (int i = s.size() - 1; i >= j; i--) {
    if (s[i] >= 'A') {
      digits.push_back(16 + s[i] - '0');
    } else {
      digits.push_back(s[i] - '0');
    }
  }
  a.digits_ = digits;
  return in;
}

/**
 * Sign
 * @brief Permite saber el síngo del objeto invocante
 */
int BigInt<16>::sign() const {
  return (is_negative_ ? -1 : 1);
}

/**
 * Sobrecarga del operador []
 * @brief Permite obtener el valor en el objeto en la posición indicada
 */
char BigInt<16>::operator[](int i) const {
  assert(i >= 0 && i < (int)digits_.size());
  return digits_[i];
}

/**
 * Sobrecarga del operador ==
 * @brief Permite obtener si ambos objetos de la clase BigInt son iguales
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator==(const BigInt<16>& a, const BigInt<16> & b) {
  if ((a.is_negative() != b.is_negative()) || (a.digits().size() != b.digits().size())) {
    return false;
  }
  for (size_t i = 0; i < a.digits().size(); i++) {
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
bool BigInt<16>::operator!=(const BigInt<16>& b) const {
  return !(*this == b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es mayor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator>(const BigInt<16>& a, const BigInt<16> & b) {
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
bool BigInt<16>::operator>=(const BigInt<16> & b) const {
  return (*this == b || *this > b);
}

/**
 * Sobrecarga del operador >
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor que el segundo
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
bool operator<(const BigInt<16>& a, const BigInt<16>& b) {
  return !(a >= b);
}

/**
 * Sobrecarga del operador >=
 * @brief Permite obtener si el primer objeto especificado de la clase BigInt es menor o igual que el segundo
 * @param b : Objeto del tipo BigInt
 */
bool BigInt<16>::operator<=(const BigInt<16>& b) const {
  return (*this == b || *this < b);
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
BigInt<16>& BigInt<16>::operator++() {
  std::vector<char> &digits = this->digits_;
  if (is_negative_ == true) {
    digits = absolute_decrease(digits_, 16);
    // Declaración de "-0"
    BigInt<16> n1;
    n1 = -n1;
    if (n1 == *this) {
      is_negative_ = false;
    }
  } else {
    digits = absolute_increase(digits_, 16);
  }
  return *this;
}

/**
 * Sobrecarga del operador ++
 * @brief Permite aumentar en una unidad el objeto invocante
 */
BigInt<16> BigInt<16>::operator++(int) {
  BigInt<16> temp(*this);
  ++(*this);
  return temp;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
BigInt<16>& BigInt<16>::operator--() {
  std::vector<char> &digits = this->digits_;
  if (is_negative_ == false) {
    digits = absolute_decrease(digits_, 16);
  } else {
    digits = absolute_increase(digits_, 16);
  }
  return *this;
}

/**
 * Sobrecarga del operador --
 * @brief Permite decrementar en una unidad el objeto invocante
 */
BigInt<16> BigInt<16>::operator--(int) {
  BigInt<16> temp(*this);
  --(*this);
  return temp;
}

/**
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<16> operator+(const BigInt<16>& a, const BigInt<16>& b) {
  BigInt<16> c;
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
 * Sobrecarga del operador +
 * @brief Permite sumar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<16>::add(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<16>*>(num);
  if (p) {
    BigInt<16> a = *this, b = *num, c;
    if (a == c || b == c) {
      if (a == c) {
        Number* final_number = new BigInt<16> (b);
        return final_number;
      } else {
        Number* final_number = new BigInt<16> (a);
        return final_number;
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
    Number* final_number = new BigInt<16> (c);
    return final_number;
  } else {
    throw "Referencia de puntero inválida!";
  }
}

/**
 * Sobrecarga del operador -
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<16> BigInt<16>::operator-(const BigInt<16> &b) const {
  BigInt<16> c;
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
 * @brief Permite restar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<16>::subtract(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<16>*>(num);
  if (p) {
    BigInt<16> a = *this, b = *num, c;
    if (*this == c || b == c) {
      if (*this == c) {
        c = -b;
      } else {
        c = -*this;
      }
      Number* final_number = new BigInt<16> (c);
      return final_number;
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
    Number* final_number = new BigInt<16> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador -
 * @brief Permite cambiar el signo del objeto invocante
 */
BigInt<16> BigInt<16>::operator-() const {
  bool condition = !(is_negative_);
  BigInt<16> n = *this;
  n.is_negative_ = condition;
  return n;
}

/**
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
BigInt<16> BigInt<16>::operator*(const BigInt<16>& b) const {
  BigInt<16> c, d, e;
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
 * Sobrecarga del operador ^
 * @brief Permite multiplicar dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<16>::multiply(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<16>*>(num);
  if (p) {  
    BigInt<16> a = *this, b = *num, c, d, e;
    bool cond_sum = false;
    if (*this == c || b == c) {
      Number* final_number = new BigInt<16> (c);
      return final_number;
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
    Number* final_number = new BigInt<16> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador /
 * @brief Permite obtener el cociente dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<16>::divide(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<16>*>(num);
  if (p) {  
    BigInt<16> a = *this, b = *num, c, d, e;
    if (b == c) {
      throw std::invalid_argument("Division por cero");
    }
    if (a == c) {
      Number* final_number = new BigInt<16> (c);
      return final_number;
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
    Number* final_number = new BigInt<16> (e);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Sobrecarga del operador %
 * @brief Permite obtener el módulo dos objetos de la clase BigInt
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<16>::modulo(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<16>*>(num);
  if (p) {  
    BigInt<16> a = *this, b = *num, c, d, e, f;
    if (b == c) {
      throw std::invalid_argument("Division por cero");
    }
    if (*this == c) {
      Number* final_number = new BigInt<16> (c);
      return final_number;
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
    Number* final_number = new BigInt<16> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * Power
 * @brief Permite elevar la potencia de un objeto de la clase BigInt elevado a otro objeto
 * @param a : Objeto del tipo BigInt
 * @param b : Objeto del tipo BigInt
 */
Number* BigInt<16>::power(const Number* num) const {
  const auto* p = dynamic_cast<const BigInt<16>*>(num);
  if (p) {  
    BigInt<16> a = *this, b = *num, c(1), d;
    if (b.is_negative_) {
      throw std::invalid_argument("Representación entera!");
    }
    while (d < b) {
      c = a * c;
      ++d;
    }
    Number* final_number = new BigInt<16> (c);
    return final_number;
  } else {
    throw "Referencia a puntero inválida!";
  }
}

/**
 * @brief Sobrecarga del operador de extracción de flujo de la clase BigInt
 * @param out : Objeto del tipo flujo estándar de salida
  * @param a : Objeto del tipo BigInt
 */
std::ostream& operator<< (std::ostream& out, const Number& num) {
  out << &num;
  return out;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en 8 2, a cualquier tipo de 8
 */
BigInt<2>::operator BigInt<2>() const {
  return *this;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en 8 base, a base 2
 */
BigInt<2>::operator BigInt<8>() const {
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
BigInt<2>::operator BigInt<10>() const {
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
BigInt<2>::operator BigInt<16>() const {
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
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 8, a base 2
 */
BigInt<8>::operator BigInt<2>() const {
  BigInt<2> result;
  BigInt<8> temp = *this, num_2(2), num_0; // Crea un objeto temporal de BigInt<8> igual al objeto actual
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
 * @brief: permite convertir un objeto en base 8, a base 8
 */
BigInt<8>::operator BigInt<8>() const {
  return *this;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 8, a base 10
 */
BigInt<8>::operator BigInt<10>() const {
  ///
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 8, a base 16
 */
BigInt<8>::operator BigInt<16>() const {
  ///
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en 10 2, a cualquier tipo de 10
 */
BigInt<10>::operator BigInt<2>() const {
  BigInt<2> result;
  BigInt<10> temp = *this, num_2(2), num_0; // Crea un objeto temporal de BigInt<10> igual al objeto actual
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
 * @brief: permite convertir un objeto en base 10, a base 8
 */
BigInt<10>::operator BigInt<8>() const {
  ///
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 10, a base 10
 */
BigInt<10>::operator BigInt<10>() const {
  return *this;
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 10, a base 16
 */
BigInt<10>::operator BigInt<16>() const {
  ///
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en 16 2, a cualquier tipo de 16
 */
BigInt<16>::operator BigInt<2>() const {
  BigInt<2> result;
  BigInt<16> temp = *this, num_2(2), num_0; // Crea un objeto temporal de BigInt<16> igual al objeto actual
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
 * @brief: permite convertir un objeto en base 16, a base 8
 */
BigInt<16>::operator BigInt<8>() const {
  ///
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 16, a base 10
 */
BigInt<16>::operator BigInt<10>() const {
  ///
}

/**
 * Operador de conversión de tipo
 * @brief: permite convertir un objeto en base 16, a base 16
 */
BigInt<16>::operator BigInt<16>() const {
  return *this;
}