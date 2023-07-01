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
#include <iostream>
#include <vector>
#include <string>

#pragma once

/**
 * Clase BigInt
 * @brief Permite la representación de números grandes
 */
template<size_t Base>
class BigInt {
 public:
  /// Constructores
  BigInt(long n = 0);
  BigInt(std::string&);
  BigInt(const char*);
  BigInt(const BigInt<Base>&); /// Constructor de copia
  /// Asignación
  BigInt<Base>& operator=(const BigInt<Base>&);
  /// Inserción y extracción en flujo
  friend std::ostream& operator<< <Base>(std::ostream&, const BigInt<Base>&); 
  friend std::istream& operator>> <Base>(std::istream&, BigInt<Base>&);
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
  /// Operadores Aritméticos
  friend BigInt<Base> operator+ <Base>(const BigInt<Base>&, const BigInt<Base>&); 
  BigInt<Base> operator-(const BigInt<Base> &) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base>&) const;
  friend BigInt<Base> operator/ <Base>(const BigInt<Base>&, const BigInt<Base>&); 
  BigInt<Base> operator%(const BigInt<Base>&) const;
  /// Potencia a^b
  friend BigInt<Base> power <Base>(const BigInt<Base>&, const BigInt<Base>&);
  /// Otros
  friend BigInt<Base> absolute_sum <Base>(const BigInt<Base>&, const BigInt<Base>&);
  friend BigInt<Base> absolute_substraction <Base>(const BigInt<Base>&, const BigInt<Base>&);
  friend bool absolute_value <Base>(const BigInt<Base>&, const BigInt<Base>&);
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
std::vector<char> absolute_increase(const std::vector<char>& digits_, size_t base) {
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
std::vector<char> absolute_decrease(const std::vector<char>& digits_, size_t base) {
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
  for (int i = std::min(a.digits_.size(), b.digits_.size()) - 1; i >= 0; i--) {
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
BigInt<Base>::BigInt(std::string& s) {
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
    }
    if (begin_not_zero) {
      aux.push_back(s[i]);
    }
  }
  aux.push_back(s[s.size() - 1]);
  s = aux;
  for (int i = s.size() - 1; i >= j; i--) {
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
template<size_t Base>
std::ostream& operator<<(std::ostream& out, const BigInt<Base>&a) {
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
 * @param out : Objeto del tipo flujo estándar de entrada
 * @param a : Objeto del tipo BigInt
 */
template<size_t Base>
std::istream& operator>>(std::istream& in, BigInt<Base>& a) {
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
  return digits_[digits_.size() - (1 + i)];
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
    throw std::invalid_argument("Division por cero");
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
    throw std::invalid_argument("Division por cero");
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
BigInt<Base> power(const BigInt<Base>& a, const BigInt<Base>& b) {
  BigInt<Base> c(1), d;
  if (b.is_negative_) {
    throw std::invalid_argument("Representación entera!");
  }
  while (d < b) {
    c = a * c;
    ++d;
  }
  return c;
}