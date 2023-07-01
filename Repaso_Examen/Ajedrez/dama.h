#pragma once

#include "ficha.h"

class Dama : public Ficha {
 public:
  Dama() {}
  Dama(const bool color, const int x, const int y) : Ficha(color, x, y) {}
  bool Mover(const int x, const int y) override;
};

bool Dama::Mover(const int x, const int y) {
  if (!((9 < x < -1) && (9 < y < -1))) {
    /// Movimientos que puede hacer la dama en el ajedrez
    if ()
  } else {
    return false;
  }
}