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
class Tabla_hash_t{

  public:
    Tabla_hash_t(unsigned tableSize = 0,
                 unsigned blockSize = 0,
                 DispersionFunction<Key>* fd = nullptr,
                 ExplorationFunction<Key>* fe = nullptr);

    ~Tabla_hash_t(void);
    bool Buscar(Key& X);
    bool Insertar(Key& X);
    void showTabla(void);
    void sumar_intento(void);
    std::vector<Sequence<Key>*>& get_v(void);
    void change_fe(ExplorationFunction<Key>* newfe);
    int get_intentos(void);

  private:
    unsigned tableSize_;
    unsigned blockSize_;
    std::vector<Sequence<Key>*> table_;
    DispersionFunction<Key>* fd_;
    ExplorationFunction<Key>* fe_;
};
#endif