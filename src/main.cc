#include <iostream>
#include <array>

#include "../include/tabla_hash.h"
#include "../include/simulator.h"

int main (int argc, char* argv[]){
  //Simulator simulator;
  //simulator.run(argc, argv);

  int ts = 50;
  DispersionFunction<Key>* fd0 = new fdModulo<Key>(ts);
  DispersionFunction<Key>* fd1 = new fdrandom<Key>(ts);
  DispersionFunction<Key>* fd2 = new fdSuma<Key>(ts);

  Tabla_hash_t<Key, DinamicSquence<Key>> table0(50, fd0);
  Tabla_hash_t<Key, DinamicSquence<Key>> table1(50, fd1);
  Tabla_hash_t<Key, DinamicSquence<Key>> table2(50, fd2);


 
  Key d;
  for (int i = 0; i < 1000; ++i ){
    d = std::rand();
    table0.insert(d);
    table1.insert(d);
    table2.insert(d);
  }


  table0.print();
  table1.print();
  table2.print();
  return 0;
}

