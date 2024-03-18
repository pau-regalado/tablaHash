#include "../include/staticSquence.h"

template <class Key>
StaticSequence<Key>::StaticSequence(int size){
  this->size = size;
  self.resize(size);
}

template <class Key>
StaticSequence<Key>::~StaticSequence(void){ }

template <class Key>
bool StaticSequence<Key>::search(const Key& X) const{
  bool found = false;
  for (int i = 0; i < size; ++i){
    if (self[i] == X){
      found = true;
    }
  }
  return found;
}

template <class Key>
bool StaticSequence<Key>::insert(const Key& X){ 
  bool no_esta = false;
  int full = 0;
  if (!isFull()){
    if (!search(X)){
      self.at(full) = X;
      full++;
      no_esta = true;
    }
  }
  return no_esta;
}

template <class Key>
bool StaticSequence<Key>::isFull(void) const{
  return !(full < size);
}

template <class Key>
void StaticSequence<Key>::print() {
  for (int i = 0; i < self.size(); ++i){
    std::cout << self[i] << " ";
  } 
}