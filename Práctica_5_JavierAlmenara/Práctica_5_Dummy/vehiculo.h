/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Práctica 5: Ordenación
 *
 * @author: Javier Almenara Herrera
 * @email: alu0101466552@ull.edu.es
 * @date: 06/04/2023
 * @file: vehiculo.h
 * @brief: Clase que permite definir un objeto del tipo vehíchulo
 */

#include <iostream>
#include <cmath>

class Vehiculo {
 public:
  Vehiculo() : matricula(0) {}
  Vehiculo(int matricula) : matricula(matricula) {}
  operator long() const {
    return (long)matricula;
  }
  operator int() const {
    return matricula;
  }
  /// Operadores de comparación
  bool operator==(const Vehiculo& other) const;
  bool operator!=(const Vehiculo& other) const;
  bool operator<(const Vehiculo& other) const;
  bool operator<=(const Vehiculo& other) const;
  bool operator>(const Vehiculo& other) const;
  bool operator>=(const Vehiculo& other) const;
  /// Operadores aritméticos
  Vehiculo operator+(const Vehiculo& other) const;
  Vehiculo operator-(const Vehiculo& other) const;
  Vehiculo operator*(const Vehiculo& other) const;
  Vehiculo operator/(const Vehiculo& other) const;
  Vehiculo operator%(const Vehiculo& other) const;
  Vehiculo& operator=(const Vehiculo& other);
  int operator[](int posicion) const;
  Vehiculo& operator+=(const Vehiculo& other);
  Vehiculo& operator-=(const Vehiculo& other);
  Vehiculo& operator*=(const Vehiculo& other);
  Vehiculo& operator/=(const Vehiculo& other);
  /// Operadores de inserción y extracción de flujo
  friend std::ostream& operator<<(std::ostream& os, const Vehiculo& vehiculo);
  friend std::istream& operator>>(std::istream& is, Vehiculo& vehiculo);
 private:
  int matricula;
};