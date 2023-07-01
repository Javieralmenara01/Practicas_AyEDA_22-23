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
 * @file: library.h
 *    Fichero que nos permite definir diferentes métodos de ordenación tal
 *    como una librería.
 */

#pragma once
#include <vector>

/** 
 * Función baja
 * @brief Función de baja que usa el algoritmo HeapSort
 * @param sec : secuencia 
 * @param n : tamaño de la secuencia
 */
template<class Key> 
void baja(int i, std::vector<Key>& sec, int n) {
  while (2 * i + 1 <= n) {
    int h1 = 2 * i + 1, h;
    int h2 = h1 + 1;
    if (h1 == n) {
      h = h1;
    } else if (sec[h1] > sec[h2]) {
      h = h1;
    } else {
      h = h2;
    }
    if (sec[h] <= sec[i]) {
      break; 
    } else {
      std::swap(sec[i],sec[h]);
      i = h;
    }
  }
}

/**
 * Función HeapSort
 * @brief Función que permite ordenar un vector con el algoritmo HeapSort
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la sequencia
 */
template<class Key> 
void HeapSortFunction(std::vector<Key>& seq, const unsigned size) {
  for (int i = (size / 2); i >= 0; i--) {
    baja(i, seq, size);
  }
  for (int i = size - 1; i > 0; i--) {
    std::swap(seq[0], seq[i]);
    baja(0, seq, i - 1) ;
  }
}

/**
 * Función HeapSort
 * @brief Función que permite ordenar un vector con el algoritmo HeapSort, mostrando la traza
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la sequencia
 */
template<class Key>
void HeapSortFunctionTrace(std::vector<Key>& seq, const unsigned size) {
  std::cout << "Fase de Insercción : " << std::endl;
  for (int i = (size / 2); i >= 0; i--) {
    baja(i, seq, size);
    PrintVector(seq); 
  }
  std::cout << "\nFase de Extracción : " << std::endl;
  for (int i = size - 1; i > 0; i--) {
    std::swap(seq[0], seq[i]);
    baja(0, seq, i - 1);
    PrintVector(seq);
  }
}

/**
 * Función Insertion
 * @brief Función que permite ordenar un vector con el algoritmo inserción
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la sequencia
 */
template<class Key>
void InsertionFunction(std::vector<Key>& seq, const unsigned size) {
  for (int i = 0; i < size; i++) { 
    int j = i;
    Key x = seq[i];
    while ((x < seq[j - 1]) && (j - 1 >= 0)) {
      seq[j] = seq[j - 1];
      j--;
    } 
    seq[j] = x;
  }
}

/**
 * Función Insertion
 * @brief Función que permite ordenar un vector con el algoritmo inserción, mostrando su traza
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la sequencia
 */
template<class Key>
void InsertionFunctionTrace(std::vector<Key>& seq, const unsigned size) {
  for (int i = 0; i < size; i++) { 
    int j = i;
    Key x = seq[i];
    while ((x < seq[j - 1]) && (j - 1 >= 0)) {
      seq[j] = seq[j - 1];
      j--;
    } 
    seq[j] = x;
    PrintVector(seq);
  }
}

/**
 * Función GetMax
 * @brief Función que permite obtener el mayor de un número, de apoyo para el algoritmo
 *        de ordenación RadixSort
 * @param seq : secuencia a ordenar
 * @param n : tamaño de la sequencia
 */
template <typename T>
T GetMax(std::vector<T> seq, const int n) {
  T max = seq[0];
  for (int i = 1; i < n; i++) {
    if (seq[i] > max) {
      max = seq[i];
    }
  }
  return max;
}

/**
 * Función Mezcla
 * @brief Función que permite mezclar de forma ordenada vectores
 * @param sec : secuencia a ordenar
 * @param ini : inicio de la sequencia
 * @param centro : centro de la sequencia
 * @param fin : final de la sequencia
 */
template <class Key>
void Mezcla(std::vector<Key>& sec, unsigned ini, unsigned cen, unsigned fin) {
  std::vector<Key> aux(fin + 1);
  unsigned i = ini, j = cen + 1;
  for (int k = ini; k <= fin; k++) {
    if (i > cen) {
      aux[k] = sec[j];
      j++;
    } else if (j > fin) {
      aux[k] = sec[i];
      i++;
    } else if (sec[i] < sec[j]) {
      aux[k] = sec[i];
      i++;
    } else {
      aux[k] = sec[j];
      j++;
    }
  }
  for (int k = ini; k <= fin; k++) {
    sec[k] = aux[k];
  }
} 

/**
 * Función MergeSort
 * @brief Función que permite ordenar un vector con el algoritmo MergeSort, mostrando su traza
 * @param sec : secuencia a ordenar
 * @param ini : inicio de la sequencia
 * @param fin : final de la sequencia
 */
template <class Key>
void MergeSortFunction(std::vector<Key>& sec, unsigned ini, unsigned fin) {
  if (ini < fin) {
    unsigned cen = (ini + fin) / 2;
    MergeSortFunction(sec, ini, cen);
    MergeSortFunction(sec, cen + 1, fin);
    Mezcla(sec, ini, cen, fin);
  } 
}

/**
 * Función Mezcla
 * @brief Función que permite mezclar de forma ordenada vectores
 * @param sec : secuencia a ordenar
 * @param ini : inicio de la sequencia
 * @param centro : centro de la sequencia
 * @param fin : final de la sequencia
 */
template <class Key>
void MezclaTrace(std::vector<Key>& sec, unsigned ini, unsigned cen, unsigned fin) {
  std::vector<Key> aux(fin + 1);
  unsigned i = ini, j = cen + 1;
  for (int k = ini; k <= fin; k++) {
    if (i > cen) {
      aux[k] = sec[j];
      j++;
    } else if (j > fin) {
      aux[k] = sec[i];
      i++;
    } else if (sec[i] < sec[j]) {
      aux[k] = sec[i];
      i++;
    } else {
      aux[k] = sec[j];
      j++;
    }
    PrintVector(aux);
  }
  for (int k = ini; k <= fin; k++) {
    sec[k] = aux[k];
  }
} 

/**
 * Función MergeSort
 * @brief Función que permite ordenar un vector con el algoritmo MergeSort, mostrando su traza
 * @param sec : secuencia a ordenar
 * @param ini : inicio de la sequencia
 * @param fin : final de la sequencia
 */
template <class Key>
void MergeSortFunctionTrace(std::vector<Key>& sec, unsigned ini, unsigned fin) {
  if (ini < fin) {
    unsigned cen = (ini + fin) / 2;
    MergeSortFunctionTrace(sec, ini, cen);
    PrintVector(sec, ini, cen);
    MergeSortFunctionTrace(sec, cen + 1, fin);
    PrintVector(sec, cen + 1, fin);
    MezclaTrace(sec, ini, cen, fin);
  } 
}

/**
 * Función RadixSort
 * @brief Función que permite ordenar un vector con el algoritmo RadixSort
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la secuencia
 */
template <class Key>
void RadixSortFunction(std::vector<Key>& seq, const unsigned size) {
  // Inicializamos el arreglo que contendrá los elementos
  std::vector<Key> output(size);
  // Obtenemos el máximo elemento
  Key max_element = GetMax(seq, size);
  // Realizamos la cuenta de los elementos para cada dígito
  for (Key exp = 1; max_element / exp > 0; exp *= 10) {
    std::vector<int> count(10, 0);
    for (int i = 0; i < size; i++) {
      count[(seq[i] / exp) % 10]++;
    }
    // Calculamos las posiciones finales de cada dígito
    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }
    // Colocamos los elementos en su posición final
    for (int i = size - 1; i >= 0; i--) {
      output[count[(seq[i] / exp) % 10] - 1] = seq[i];
      count[(seq[i] / exp) % 10]--;
    }
    // Copiamos el vector ordenado al vector original
    for (int i = 0; i < size; i++) {
      seq[i] = output[i];
    }
  }
}

/**
 * Función RadixSort
 * @brief Función que permite ordenar un vector con el algoritmo RadixSort, mostrando su traza
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la secuencia
 */
template <class Key>
void RadixSortFunctionTrace(std::vector<Key>& seq, const unsigned size) {
  // Inicializamos el arreglo que contendrá los elementos
  std::vector<Key> output(size);
  // Obtenemos el máximo elemento
  Key max_element = GetMax(seq, size);
  // Realizamos la cuenta de los elementos para cada dígito
  for (Key exp = 1; max_element / exp > 0; exp *= 10) {
    std::vector<int> count(10, 0);
    for (int i = 0; i < size; i++) {
      count[(seq[i] / exp) % 10]++;
    }
    PrintVector(count);
    // Calculamos las posiciones finales de cada dígito
    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }
    PrintVector(count);
    // Colocamos los elementos en su posición final
    for (int i = size - 1; i >= 0; i--) {
      output[count[(seq[i] / exp) % 10] - 1] = seq[i];
      count[(seq[i] / exp) % 10]--;
    }
    // Copiamos el vector ordenado al vector original
    for (int i = 0; i < size; i++) {
      seq[i] = output[i];
    }
    PrintVector(seq);
  }
}

/**
 * Función DeltaSort
 * @brief Función que permite ordenar un vector con el algoritmo DeltaSort
 * @param sec : secuencia a ordenar
 * @param n : tamaño de la secuencia
 */
template<class Key> 
void DeltaSort(int delta, std::vector<Key>& sec, int n) {
  for (int i = delta; i < n; i++){
    Key x = sec[i];
    int j = i;
    while ((j >= delta) && (x < sec[j - delta])){
      sec[j] = sec[j - delta];
      j = j - delta;
    }
    sec[j] = x;
  }
}

/**
 * Función RadixSort
 * @brief Función que permite ordenar un vector con el algoritmo RadixSort, mostrando su traza
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la secuencia
 */
template<class Key> 
void DeltaSortTrace(int delta, std::vector<Key>& sec, int n) {
  for (int i = delta; i < n; i++){
    Key x = sec[i];
    int j = i ;
    while ((j >= delta) && (x < sec[j - delta])){
      sec[j] = sec[j - delta];
      j = j - delta;
    }
    sec[j] = x;
    PrintVector(sec);
  }
}

/**
 * Función ShellSort
 * @brief Función que permite ordenar un vector con el algoritmo ShellSort
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la secuencia
 * @param alpha : valor de alpha 
 */
template<class Key> 
void ShellSortFunction(std::vector<Key>& seq, const unsigned size, const double alpha) {
  int delta = size;
  while (delta > 1) {
    delta = (double)delta * alpha;
    DeltaSort(delta, seq, (int)size);
  }
}

/**
 * Función ShellSort
 * @brief Función que permite ordenar un vector con el algoritmo ShellSort
 * @param seq : secuencia a ordenar
 * @param size : tamaño de la secuencia
 * @param alpha : valor de alpha 
 */
template<class Key> 
void ShellSortFunctionTrace(std::vector<Key>& seq, const unsigned size, const double alpha) {
  int delta = size;
  while (delta > 1) {
    std::cout << "Delta : " << delta << std::endl;
    delta = (double)delta * alpha;
    DeltaSortTrace(delta, seq, (int)size);
    PrintVector(seq);
  }
}

/**
 * Función QuickSort
 * @brief Función que permite ordenar un vector con el algoritmo QuickSort
 * @param seq : secuencia a ordenar
 * @param inicio : inicio de la secuencia
 * @param fin : final de la secuencia
 */
template<class Key> 
void QuickSortFunction(std::vector<Key>& seq, const unsigned ini, const unsigned fin) {
  unsigned i = ini, f = fin;
  Key p = seq[(i + f) / 2];
  while (i <= f) {
    while (seq[i] < p) i++;
    while (seq[f] > p) f--;
    if (i <= f) {
      std::swap(seq[i], seq[f]);
      i++;
      f--;
    }
  }
  if (i < fin) {
    QuickSortFunction(seq, i, fin);
  }
  if (ini < f) {
    QuickSortFunction(seq, ini, f);
  }
}

/**
 * Función QuickSort
 * @brief Función que permite ordenar un vector con el algoritmo QuickSort, mostrando su traza
 * @param seq : secuencia a ordenar
 * @param inicio : inicio de la secuencia
 * @param fin : final de la secuencia
 */
template<class Key> 
void QuickSortFunctionTrace(std::vector<Key>& seq, const unsigned ini, const unsigned fin) {
  unsigned i = ini, f = fin;
  Key p = seq[(i + f) / 2];
  std::cout << "Pivote = " << p << "   i:" << i << " f:" << f << std::endl;
  PrintVector(seq); 
  while (i <= f) {
    while (seq[i] <= p) i++;
    while (seq[f] => p) f--;
    if (i <= f) {
      std::swap(seq[i], seq[f]);
      if (i < fin) i++;
      if (f > ini) f--;
    }
    PrintVector(seq); 
    std::cout << "   i:" << i << " f:" << f << std::endl;
    std::cin.get();
  }
  if (ini < f) {
    QuickSortFunctionTrace(seq, ini, f);
  }
  if (i < fin) {
    QuickSortFunctionTrace(seq, i, fin);
  }
}