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

#include "vehiculo.h"

/**
 * Constructor
 */ 
Vehiculo::Vehiculo() {
  matricula_ = "0000AAA";
}

/**
 * Sobrecarga de Operador de Asignación
 */ 
void Vehiculo::operator=(const Vehiculo& v) {
  matricula_ = v.matricula_;
}

/**
 * Sobrecarga de Operador de Asignación
 */ 
void Vehiculo::operator=(const int v) {
  matricula_ = std::to_string(v);
}

/**
 * Sobrecarga de Operador ==
 */ 
bool operator==(const Vehiculo& v1, const Vehiculo& v2) {
  return v1.matricula_ == v2.matricula_;
}

/**
 * Sobrecarga de Operador de Conversión de Tipo long
 */ 
Vehiculo::operator long() const {
  std::hash<std::string> hash_funct;
  return (long)hash_funct(matricula_);
}

/**
 * Sobrecarga de Operador de Conversión de Tipo int
 */ 
Vehiculo::operator int() const {
  std::hash<std::string> hash_funct;
  return (int)hash_funct(matricula_);
}

/**
 * Sobrecarga de Operador de Conversión de Tipo unsigned
 */ 
Vehiculo::operator unsigned() const {
  std::hash<std::string> hash_funct;
  return (unsigned)hash_funct(matricula_);
}

/**
 * Sobrecarga de Operador <<
 * @param in : Flujo de entrada
 * @param v : objeto de la clase vehículo
 */ 
std::istream& operator>>(std::istream& in, Vehiculo& v) {
  in >> v.matricula_;
  return in;
}

/**
 * Sobrecarga de Operador >>
 * @param out : Flujo de salida
 * @param v : objeto de la clase vehículo
 */ 
std::ostream& operator<<(std::ostream& out, const Vehiculo& v) {
  out << v.matricula_;
  return out;
}
