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

template<size_t Base = 10>
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
  BigInt<Base> operator+=(const BigInt<Base>&);
  BigInt<Base> operator-(const BigInt<Base> &) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base>&) const;
  friend BigInt<Base> operator/ <Base>(const BigInt<Base>&, const BigInt<Base>&); 
  BigInt<Base> operator%(const BigInt<Base>&) const;
  /// Potencia a^b
  friend BigInt<Base> power <Base>(const BigInt<Base>&, const BigInt<Base>&);
  /// Factorial 
  friend BigInt<Base> factorial <Base>(const BigInt<Base>&);
  /// Fibonacci
  friend BigInt<Base> fibonacci <Base>(int); 
  /// Catalan
  friend BigInt<Base> catalan <Base>(int);
  /// Otros
  friend BigInt<Base> absolute_sum <Base>(const BigInt<Base>&, const BigInt<Base>&);
  friend BigInt<Base> absolute_substraction <Base>(const BigInt<Base>&, const BigInt<Base>&);
  friend bool absolute_value <Base>(const BigInt<Base>&, const BigInt<Base>&);

 private:
  std::vector<char> digits_;
  bool is_negative_ = false;
};

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

template<size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
}

template<size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& n) {
  digits_ = n.digits_;
  is_negative_ = n.is_negative_;
  return *this;
}

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

template<size_t Base>
int BigInt<Base>::sign() const {
  return (is_negative_ ? -1 : 1);
}

template<size_t Base>
char BigInt<Base>::operator[](int i) const {
  return digits_[digits_.size() - (1 + i)];
}

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

template<size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& b) const {
  return !(*this == b);
}

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

template<size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> & b) const {
  return (*this == b || *this > b);
}

template<size_t Base>
bool operator<(const BigInt<Base>& a, const BigInt<Base>& b) {
  return !(a >= b);
}

template<size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& b) const {
  return (*this == b || *this < b);
}

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

template<size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {
  BigInt<Base> temp(*this);
  ++(*this);
  return temp;
}

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

template<size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {
  BigInt<Base> temp(*this);
  --(*this);
  return temp;
}

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

template<size_t Base>
BigInt<Base> BigInt<Base>::operator+=(const BigInt<Base>& b) {
  return (*this + b);
}

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

template<size_t Base>
BigInt<Base> BigInt<Base>::operator-() const {
  bool condition = !(is_negative_);
  BigInt<Base> n = *this;
  n.is_negative_ = condition;
  return n;
}

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

template<size_t Base>
BigInt<Base> factorial(const BigInt<Base>& a) {
  BigInt<Base> c(1), d(1), e;
  if (a == e) {
    return c;
  }
  e = a;
  while (e > d) {
    c = c * e;
    --e;
  }
  return c;
}

template<size_t Base>
BigInt<Base> fibonacci(int n) {
  /// Devuelve la posición n de la serie de Fibonacci
  BigInt a(1), b(1), c;
  if(!n)
    return c;
  n--;
  while(n--) {
    c = a + b;
    b = a;
    a = c;
  }
  return b;
} 


template<size_t Base>
BigInt<Base> catalan(int n) { 
  /// Devuelve la posición n de la serie de Fibonacci
  BigInt a(1), b;
  for (int i = 2; i <= n; i++)
    a = a * i;
  b = a;
  for (int i = n + 1; i <= 2 * n; i++)
    b = b * i;
  a = a * a;
  a = a * (n + 1);
  b = b / a;
  return b;
}