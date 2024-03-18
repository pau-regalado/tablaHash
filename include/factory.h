#ifndef __FACTORY__ 
#define __FACTORY__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>


enum feTypes { LINEAL, CUADRATICA, DOBLE_DISPERSION, REDISPERSION, SIN_EXPLORACION };
enum fdTypes { MODULO, SUMA, RANDOM};

class Factory {
  private:


  public:
    Factory();
    ~Factory();

    Lattice* generate(int argc, char* argv[]);
};

#endif