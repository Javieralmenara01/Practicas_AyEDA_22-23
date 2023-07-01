#include <string> 
#include <iostream>
#include <vector>

class Ficha {
 public:
  Ficha() {}
  Ficha(const bool color, const int x, const int y) : color_{color}, x_{x}, y_{y} {}
  std::string ObtenerColor() { return ((color_) ? "blanco" : "negro"); }
  bool ObtenerColorBool() { return color_; }
  virtual bool Mover(const int x, const int y) = 0;
  int x() const { return x_; }
  int y() const { return y_; }
 private:
  bool color_;
  int x_;
  int y_;
};