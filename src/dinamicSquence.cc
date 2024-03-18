#include "../include/dinamicSquence.h"

template <class Key>
DinamicSquence<Key>::DinamicSquence(int Size){ }

template <class Key>
DinamicSquence<Key>::~DinamicSquence(void){}

template <class Key>
bool DinamicSquence<Key>::search(const Key& X) const{
  bool encontrado = false;
  for (int i = 0; i < self.size(); ++i){
    if (self.at(i) == X){
      encontrado = true;
    }
  }
  return encontrado;
}

template <class Key>
bool DinamicSquence<Key>::insert(const Key& X){
  bool insert = false;
  if (!search(X)){
    self.push_back(X);
    insert = true;
  }
  return insert;
}

template <class Key>
void DinamicSquence<Key>::print() {
  for (int i = 0; i < self.size(); ++i){
    std::cout << self[i] << " ";
  } 
}