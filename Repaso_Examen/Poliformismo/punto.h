#include "elemento_grafico.h"

class Punto : public ElementoGrafico {
 public:
  Punto() : ElementoGrafico() {}
  Punto(int x, int y) : ElementoGrafico(x, y) {}
  void dibujar() const override {
    std::cout << "Punto en (" << getX() << ", " << getY() << ")" << std::endl;
  }
};