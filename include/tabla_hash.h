#ifndef __TABLA_HASH__
#define __TABLA_HASH__

#include <vector>
#include <array>
#include <iostream>

#include "dinamicSquence.h"
#include "staticSquence.h"
#include "dispersionFunction.h"
#include "explorationFunction.h"

const unsigned kDefaultSize = 10;
const unsigned kDefaultVector = 3;

template <class Key, class Container=StaticSequence<Key>>
class Tabla_hash_t {

  public:
    Tabla_hash_t(unsigned tableSize = 0,
                 unsigned blockSize = 0,
                 DispersionFunction<Key>* fd = nullptr,
                 ExplorationFunction<Key>* fe = nullptr);
    Tabla_hash_t(unsigned tableSize = 0,
                 DispersionFunction<Key>* fd = nullptr);

    ~Tabla_hash_t(void);

    bool search(Key& X);
    bool insert(Key& X);
    
    void print();
    int getIntentos();
    void resetIntentos();

  private:
    unsigned tableSize;
    unsigned blockSize;
    std::vector<Sequence<Key>*> table;
    DispersionFunction<Key>* fd;
    ExplorationFunction<Key>* fe;
    int intentos;

};

template <class Key, class Container>
Tabla_hash_t<Key, Container>::Tabla_hash_t(unsigned tableSize, DispersionFunction<Key>* fd) {
  this->tableSize = tableSize;
  this->fd = fd;
  this->fe = nullptr;
  this->intentos = 0;
  this->table.resize(tableSize);
  for (int i = 0; i < tableSize; ++i){
    this->table[i] = new DinamicSquence<Key>;
  }                   
}

template <class Key, class Container>
Tabla_hash_t<Key, Container>::Tabla_hash_t(unsigned tableSize,
                  unsigned blockSize,
                  DispersionFunction<Key>* fd,
                  ExplorationFunction<Key>* fe) {
  this->tableSize = tableSize;
  this->fd = fd;
  this->blockSize = blockSize;
  this->table.resize(tableSize);
  this->fe = fe;
  this->intentos = 0;
    
  for (int i = 0; i < tableSize; ++i){
    this->table[i] = new StaticSequence<Key>(blockSize);
  }
}

template <class Key, class Container>
Tabla_hash_t<Key, Container>::~Tabla_hash_t(void){
  if (fe != nullptr) {  
    delete fe;
  } 
  delete fd;
}

template <class Key, class Container>
bool Tabla_hash_t<Key, Container>::search(Key& X){
  if (table[(*fd)(X)]->search(X)){
    intentos++;
    return true;
  }
  
  if (table[(*fd)(X)]->isFull()) {
    unsigned iter = 1;
    do{
      if (table[((*fd)(X) + (*fe)(X,iter)) % tableSize]->search(X)) {
        return true;
      }
      if (!table[((*fd)(X) + (*fe)(X,iter)) % tableSize]->isFull()) {
        return false;
      }
      iter++;
      intentos++;
    } while(iter <= tableSize);
  }

  return false;
}

template <class Key, class Container>
bool Tabla_hash_t<Key, Container>::insert(Key& X){
  unsigned iter = 1;
  if (search(X)) {
    return false;
  }

  if (!this->table[(*fd)(X)]->isFull()){
    intentos++;
    return this->table[(*fd)(X)]->insert(X);
  } else {
    do{
      if(!this->table[((*fd)(X) + (*fe)(X,iter)) % tableSize]->isFull()){
        std::cout << "Esta lleno. Hace uso de función de exploración" << std::endl;
        return this->table[((*fd)(X) + (*fe)(X,iter)) % tableSize]->insert(X);
      } 
      iter++;
      intentos++;
    } while(iter <= this->tableSize);
  }
  return false;
}

template <class Key, class Container>
void Tabla_hash_t<Key, Container>::print() {
  std::cout << std::endl;
  std::cout << "Tabla Hash: " << std::endl;
  for (int i = 0; i < this->tableSize; ++i){
    std::cout << "[" << i << "]: ";
    this->table[i]->print();
  }
}

template <class Key, class Container>
int Tabla_hash_t<Key, Container>::getIntentos(void){
  return intentos;
}

template <class Key, class Container>
void Tabla_hash_t<Key, Container>::resetIntentos(void){
  intentos = 0;
}

#endif