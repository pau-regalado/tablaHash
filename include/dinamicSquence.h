#ifndef _DINAMIC_SQUENCE_
#define _DINAMIC_SQUENCE_

#include <vector>
#include <iostream>

#include "sequence.h"
 
template <class Key>
class DinamicSquence: public Sequence<Key>{

  public:
    DinamicSquence();
    ~DinamicSquence(void);

    bool search(const Key& X) const;
    bool insert(const Key&X);
    bool isFull(void) const { return false; }
    void print();
    
  private:
    std::vector<Key> self;

};

template <class Key>
DinamicSquence<Key>::DinamicSquence(){ }

template <class Key>
DinamicSquence<Key>::~DinamicSquence(void){ }

template <class Key>
bool DinamicSquence<Key>::search(const Key& X) const{
  for (int i = 0; i < self.size(); ++i){
    if (self[i] == X){
      return true;
    }
  }
  return false;
}

template <class Key>
bool DinamicSquence<Key>::insert(const Key& X){
  if (!search(X)){
    self.push_back(X);
    return true;
  }
  return false;
}

template <class Key>
void DinamicSquence<Key>::print() {
  //for (int i = 0; i < self.size(); ++i){
    //std::cout << self[i] << " ";
    std:: cout << self.size() << std::endl;
  //} 
}

#endif