#ifndef __STATIC_SQUENCE__
#define __STATIC_SQUENCE__

#include <vector>
#include <array>
#include <list>
#include <iostream>

#include "sequence.h"
 
template <class Key>
class StaticSequence: public Sequence<Key>{

  public:
    StaticSequence(const int size = 0);
    ~StaticSequence(void);

    bool search(const Key& X) const;
    bool insert(const Key&X);
    bool isFull(void) const;
    void print();
  
  private:
    int size;
    std::vector<Key> self;
};

template <class Key>
StaticSequence<Key>::StaticSequence(int size){
  this->size = size;
}

template <class Key>
StaticSequence<Key>::~StaticSequence(void){ }

template <class Key>
bool StaticSequence<Key>::search(const Key& X) const{
  for (int i = 0; i < self.size(); ++i){
    if (self[i] == X){
      return true;
    }
  }
  return false;
}

template <class Key>
bool StaticSequence<Key>::insert(const Key& X){ 
  if (!isFull() && !search(X)){
    self.push_back(X);
    return true;
  }
  return false;
}

template <class Key>
bool StaticSequence<Key>::isFull(void) const{
  return self.size() >= size;
}

template <class Key>
void StaticSequence<Key>::print() {
  for (int i = 0; i < self.size(); ++i){
    std::cout << self[i] << " ";
  } 
}

#endif