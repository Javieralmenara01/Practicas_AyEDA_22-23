#pragma once

#include "linea.h"

class LineaVertical : public Linea {
 public:
  LineaVertical() : Linea() {}
  LineaVertical(int x, int y, int x2, int y2) : Linea(x, y, x2, y2) {}
  void dibujar() const override {
    std::cout << "Linea vertical en (" << getX() << ", " << getY() << ") y (" << getX() << ", " << getY2() << ")" << std::endl;
  }
};
