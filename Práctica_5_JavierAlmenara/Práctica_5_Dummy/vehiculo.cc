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
 * @file: vehiculo.cc
 * @brief: Clase que permite definir un objeto del tipo vehículo
 */

#include "vehiculo.h"

/**
 * @brief Operador de igualdad.
 *        Compara dos vehículos por su matrícula.
 * @param other Otro vehículo a comparar.
 * @return true si las matrículas son iguales, false en caso contrario.
 */bool Vehiculo::operator==(const Vehiculo& other) const {
  return this->matricula == other.matricula;
}

/**
 * @brief Operador de desigualdad.
 *        Compara dos vehículos por su matrícula.
 * @param other Otro vehículo a comparar.
 * @return true si las matrículas son diferentes, false en caso contrario.
 */
bool Vehiculo::operator!=(const Vehiculo& other) const {
  return !(*this == other);
}

/**
 * @brief Operador menor que.
 *        Compara dos vehículos por su matrícula.
 * @param other Otro vehículo a comparar.
 * @return true si la matrícula del vehículo actual es menor que la del otro vehículo, false en caso contrario.
 */
bool Vehiculo::operator<(const Vehiculo& other) const {
  return this->matricula < other.matricula;
}

/**
 * @brief Operador menor o igual que.
 *        Compara dos vehículos por su matrícula.
 * @param other Otro vehículo a comparar.
 * @return true si la matrícula del vehículo actual es menor o igual que la del otro vehículo, false en caso contrario.
 */
bool Vehiculo::operator<=(const Vehiculo& other) const {
  return (*this == other) || (*this < other);
}

/**
 * @brief Operador menor que.
 *        Compara dos vehículos por su matrícula.
 * @param other Otro vehículo a comparar.
 * @return true si la matrícula del vehículo actual es menor que la del otro vehículo, false en caso contrario.
 */
bool Vehiculo::operator>(const Vehiculo& other) const {
  return !(*this <= other);
}

/**
 * @brief Operador mayor o igual que.
 *        Compara dos vehículos por su matrícula.
 * @param other Otro vehículo a comparar.
 * @return true si la matrícula del vehículo actual es mayor o igual que la del otro vehículo, false en caso contrario.
 */
bool Vehiculo::operator>=(const Vehiculo& other) const {
  return !(*this < other);
}

/**
 * @brief Operador suma
 *        Suma dos vehículos por su matrícula.
 * @param other Otro vehículo a sumar.
 * @return la suma de las matriculas en un nuevo vehículo
 */
Vehiculo Vehiculo::operator+(const Vehiculo& other) const {
  int nuevaMatricula = this->matricula + other.matricula;
  return Vehiculo(nuevaMatricula);
}

/**
 * @brief Operador resta
 *        Resta dos vehículos por su matrícula.
 * @param other Otro vehículo a restar.
 * @return la resta de las matriculas en un nuevo vehículo
 */
Vehiculo Vehiculo::operator-(const Vehiculo& other) const {
  int nuevaMatricula = this->matricula - other.matricula;
  return Vehiculo(nuevaMatricula);
}

/**
 * @brief Operador multiplica
 *        Multiplica dos vehículos por su matrícula.
 * @param other Otro vehículo a multiplicar.
 * @return la multiplicación de las matriculas en un nuevo vehículo
 */
Vehiculo Vehiculo::operator*(const Vehiculo& other) const {
  int nuevaMatricula = this->matricula * other.matricula;
  return Vehiculo(nuevaMatricula);
}

/**
 * @brief Operador división
 *        Divide dos vehículos por su matrícula.
 * @param other Otro vehículo a dividir (dividendo).
 * @return el cociente de la división de las matriculas en un nuevo vehículo
 */
Vehiculo Vehiculo::operator/(const Vehiculo& other) const {
  int nuevaMatricula = this->matricula / other.matricula;
  return Vehiculo(nuevaMatricula);
}

/**
 * @brief Operador módulo
 *        Obtiene el resto de dos vehículos por su matrícula.
 * @param other Otro vehículo a dividir.
 * @return el resto de la división de las matriculas en un nuevo vehículo
 */
Vehiculo Vehiculo::operator%(const Vehiculo& other) const {
  int nuevaMatricula = this->matricula % other.matricula;
  return Vehiculo(nuevaMatricula);
}

/**
 * @brief Operador asignación
 *        Asigna al objeto actual otro pasado
 * @param other Otro vehículo a asignar
 * @return la referencia a un vehículo
 */
Vehiculo& Vehiculo::operator=(const Vehiculo& other) {
  this->matricula = other.matricula;
  return *this;
}
  
/**
 * @brief Sobrecarga del operador [] para obtener un dígito de la matrícula
 * @param posicion La posición del dígito a obtener (0-3)
 * @return El dígito correspondiente a la posición
 * @throw std::out_of_range si la posición es inválida
 */
int Vehiculo::operator[](int posicion) const {
  if (posicion < 0 || posicion >= 4) {
    throw std::out_of_range("Posicion invalida");
  }
  /// Obtenemos el dígito correspondiente
  int digito = (this->matricula / static_cast<int>(pow(10, posicion))) % 10;
  return digito;
}

/**
 * @brief Sobrecarga del operador += para sumar dos matrículas
 * @param other La matrícula a sumar
 * @return La matrícula resultante de la suma
 */
Vehiculo& Vehiculo::operator+=(const Vehiculo& other) {
  this->matricula += other.matricula;
  return *this;
}

/**
 * @brief Sobrecarga del operador -= para restar dos matrículas
 * @param other La matrícula a restar
 * @return La matrícula resultante de la resta
 */
Vehiculo& Vehiculo::operator-=(const Vehiculo& other) {
  this->matricula -= other.matricula;
  return *this;
}

/**
 * @brief Sobrecarga del operador *= para multiplicar dos matrículas
 * @param other La matrícula a multiplicar
 * @return La matrícula resultante de la multiplicación
 */
Vehiculo& Vehiculo::operator*=(const Vehiculo& other) {
  this->matricula *= other.matricula;
  return *this;
}

/**
 * @brief Sobrecarga del operador /= para dividir dos matrículas
 * @param other La matrícula a dividir (dividendo)
 * @return La matrícula resultante de la multiplicación
 */
Vehiculo& Vehiculo::operator/=(const Vehiculo& other) {
  this->matricula /= other.matricula;
  return *this;
}

/**
 * @brief Sobrecarga del operador de inserción de flujo para imprimir la matrícula del vehículo.
 * @param os Flujo de salida.
 * @param vehiculo Vehículo cuya matrícula se desea imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Vehiculo& vehiculo) {
  os << vehiculo.matricula;
  return os;
}

/**
 * @brief Sobrecarga del operador de extracción de flujo para leer la matrícula del vehículo.
 * @param is Flujo de entrada.
 * @param vehiculo Vehículo al que se desea asignar la matrícula leída.
 * @return std::istream& Referencia al flujo de entrada.
 */
std::istream& operator>>(std::istream& is, Vehiculo& vehiculo) {  
  int matricula;
  is >> matricula;
  vehiculo.matricula = matricula;
  return is;
}