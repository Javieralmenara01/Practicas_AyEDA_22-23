#include <string>
#include <iostream>
#include <vector>

template <typename T>
void Ordenar(std::vector<T>& vector, const int size) {
  int inicio = 0, final = size - 1;
  while (inicio <= final) {
    int posicion = inicio;
    for (int i = inicio; i <= final; i++) {
      if (vector[i] < vector[posicion]) {
        posicion = i;
      }
    }
    if (posicion != inicio) {
      std::swap(vector[inicio], vector[posicion]);
    }
    inicio++;
    posicion = final;
    for (int i = final; i >= inicio; i--) {
      if (vector[i] > vector[posicion]) {
        posicion = i;
      }
    }
    if (posicion != final) {
      std::swap(vector[final], vector[posicion]);
    }
    final--;
  }

}




int main() {
  // secuencia desordenada
  std::vector<int> vector = { 12, 3, 4, 5, 1, 13, 14, 11, 9};
  // secuencia ordenada
  Ordenar(vector, vector.size());
  for (int i = 0; i < vector.size(); i++) {
    std::cout << vector[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
