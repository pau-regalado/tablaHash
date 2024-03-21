#ifndef __DISPERSION_FUNCTION__
#define __DISPERSION_FUNCTION__

#include <random>

template<class Key>
class DispersionFunction{
  
  public:
    virtual unsigned operator()(const Key& k) const = 0;
};

template<class Key>
class fdModulo: public DispersionFunction<Key>{
  public:
  fdModulo(const unsigned n): nDatos(n){}
  
  unsigned operator()(const Key& k) const {
    return long(k) % nDatos;
  }
  
  private:
    unsigned nDatos;
};

template<class Key>
class fdSuma: public DispersionFunction<Key>{
  public:

    fdSuma(const unsigned n): nDatos(n){}
    
    unsigned operator()(const Key& k) const {
      int y, d = 0;
      int x = long(k);
      while (x > 0) {
        y = x % 10;
        d += y;
        x /= 10;
      }
      return d % nDatos;
    }
  private:
    unsigned nDatos;
};

template<class Key>
class fdrandom: public DispersionFunction<Key>{
  public:

    fdrandom(const unsigned n): nDatos(n){}
    
    unsigned operator()(const Key& k) const {
      srand(long(k));
      return rand() % nDatos;
    }
  private:
    unsigned nDatos;
};

#endif