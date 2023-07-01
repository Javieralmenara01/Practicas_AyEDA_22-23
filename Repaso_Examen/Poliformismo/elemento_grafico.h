
#pragma once

#include "iostream"

class ElementoGrafico {
 public:  
  ElementoGrafico() { x = 0; y = 0; }
  ElementoGrafico(int x, int y) { this->x = x; this->y = y; }
  void setX(int x) { this->x = x; }
  int getX() const { return x; }
  void setY(int y) { this->y = y; }
  int getY() const { return y; }
  virtual void dibujar() const = 0;
 private:
  int x;
  int y;
};  