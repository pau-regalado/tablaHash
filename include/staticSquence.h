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
    virtual bool isFull(void) const = 0;
    void print();
  
  private:
    int size;
    std::vector<Key> self;
};

#endif