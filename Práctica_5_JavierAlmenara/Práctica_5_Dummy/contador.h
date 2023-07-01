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
 * @file: contador.h
 * @brief: Declaración de la clase contador
 */

#pragma once

class Contador {
 public:
  static void Resetear() { // método para resetear el contador
    cuenta = 0;
  }
  static void Contar() { // método para aumentar en 1 el contador
    cuenta++;
  }
  static int Valor() { // método para devolver el valor actual del contador
    return cuenta;
  }
 private:
  static int cuenta; // atributo estático para contar sucesos
};