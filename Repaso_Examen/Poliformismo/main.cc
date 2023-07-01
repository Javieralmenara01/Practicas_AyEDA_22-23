// Repaso Examen  
// Javier

#include <iostream>
#include "elemento_grafico.h"
#include "punto.h"
#include "linea.h"
#include "linea_vertical.h"
#include "linea_horizontal.h"

int main() {
  ElementoGrafico* elementos[4];
  elementos[0] = new Punto(1, 2);
  elementos[1] = new Linea(1, 2, 3, 4);
  elementos[2] = new LineaVertical(1, 2, 3, 4);
  elementos[3] = new LineaHorizontal(1, 2, 3, 4);

  for (int i = 0; i < 4; i++) {
    elementos[i]->dibujar();
  }

  return 0;
}