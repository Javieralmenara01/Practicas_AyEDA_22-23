// Clase Tablero de Ajedrez

#pragma once
#include <iostream>
#include "ficha.h"

class TableroAjedrez {
 public:
  TableroAjedrez();
  bool MoverFicha(int x, int y, int x2, int y2);
  void ImprimirTablero();
 private:
  int filas_;
  int columnas_;
  Ficha** tablero_;
};

TableroAjedrez::TableroAjedrez() {
  filas_ = 8;
  columnas_ = 8;
  tablero_ = new Ficha*[filas_];
  for (int i = 0; i < filas_; i++) {
    tablero_[i] = new Ficha[columnas_];
  }
  // Colocar fichas blancas
  for (int i = 0; i < filas_; i++) {
    for (int j = 0; j < columnas_; j++) {
      tablero_[i][j] = new Ficha();
    }
  }
}

void TableroAjedrez::ImprimirTablero() {  

}