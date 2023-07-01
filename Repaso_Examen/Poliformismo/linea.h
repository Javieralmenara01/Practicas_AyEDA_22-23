
#pragma once

#include "elemento_grafico.h"

class Linea : public ElementoGrafico {
 public:
  Linea() : ElementoGrafico() {}
  Linea(int x, int y, int x2, int y2) : ElementoGrafico(x, y) { this->x2 = x2; this->y2 = y2; }
  int getX2() const { return x2; }
  void setX2(int x2) { this->x2 = x2; }
  int getY2() const { return y2; }
  void setY2(int y2) { this->y2 = y2; }
  void dibujar() const override {
    std::cout << "Linea en (" << getX() << ", " << getY() << ") y (" << x2 << ", " << y2 << ")" << std::endl;
  }
 private:
  int x2;
  int y2;
};
