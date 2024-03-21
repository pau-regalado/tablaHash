#include <iostream>
#include <array>

#include "../include/simulator.h"

template <class Key>
void probar_tabla(Tabla_hash_t<Key>* t){
  Key n;
  for (int i = 0; i < 20; ++i ){
    n = std::rand();
    t->Insertar(n);
  }
} 

int main (int argc, char* argv[]){
  Simulator simulator;
  simulator.run(argc, argv);
  return 0;
}