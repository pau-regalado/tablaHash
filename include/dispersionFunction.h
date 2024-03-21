#ifndef __DISPERSION_FUNCTION__
#define __DISPERSION_FUNCTION__

#include <random>

template<class Key>
class DispersionFunction {
  
  public:
    DispersionFunction(const unsigned nDatos) : nDatos(nDatos) { }
    virtual unsigned operator()(const Key& k) const = 0;

  protected:
    unsigned nDatos;
};

template<class Key>
class fdModulo: public DispersionFunction<Key>{
  public:
    fdModulo(const unsigned n): DispersionFunction<Key>(n) {}
  
    unsigned operator()(const Key& k) const {
      return long(k) % this->nDatos;
    }
};

template<class Key>
class fdSuma: public DispersionFunction<Key>{
  public:

    fdSuma(const unsigned n): DispersionFunction<Key>(n) {}
    
    unsigned operator()(const Key& k) const {
      int y, d = 0;
      int x = long(k);
      while (x > 0) {
        y = x % 10;
        d += y;
        x /= 10;
      }
      return d % this->nDatos;
    }
};

template<class Key>
class fdrandom: public DispersionFunction<Key>{
  public:

    fdrandom(const unsigned n): DispersionFunction<Key>(n) {}
    
    unsigned operator()(const Key& k) const {
      srand(long(k));
      return rand() % this->nDatos;
    }
};

#endif