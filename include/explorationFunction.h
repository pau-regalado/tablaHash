#ifndef __EXPLORATION_FUNCTION__
#define __EXPLORATION_FUNCTION__

#include <random>
#include "dispersionFunction.h"

template<class Key>
class ExplorationFunction { 
  public:
    virtual unsigned operator()(const Key& k, unsigned i) const = 0;
};

template<class Key>
class feLineal: public ExplorationFunction<Key>{
  public:
    unsigned operator()(const Key& k, unsigned i) const { return i; }
};

template<class Key>
class feCuadratica: public ExplorationFunction<Key>{
  public:
    unsigned operator()(const Key& k, unsigned i) const { return i * i; }
};

template<class Key>
class feDobleDispersion: public ExplorationFunction<Key>{
  public:
    feDobleDispersion(DispersionFunction<Key>* fd): fd_(fd) {}
    feDobleDispersion(void){ delete fd_; }
    unsigned operator()(const Key& k, unsigned i) const { return (*fd_)(k) * i; }

  private:
    DispersionFunction<Key>* fd_;
};

template<class Key>
class feRedispersion: public ExplorationFunction<Key>{

  public:
    feRedispersion(int ts) {
      family = {new fdModulo<Key>(ts), new fdSuma<Key>(ts), new fdrandom<Key>(ts)};
    }
    ~feRedispersion(void) { }
    unsigned operator()(const Key& k, unsigned i) const {
      return (*family[i % family.size()])(k);
    }

  private:
    std::vector<DispersionFunction<Key>*> family;
};

#endif