#ifndef _DINAMIC_SQUENCE_
#define _DINAMIC_SQUENCE_

#include <vector>
#include <array>
#include <list>
#include <iostream>
#include "sequence.h"
 
template <class Key>
class DinamicSquence: public Sequence<Key>{

  public:

    DinamicSquence(const int Size = 0);
    //DinamicSquence(std::list<Key>& New);
    ~DinamicSquence(void);

    virtual bool search(const Key& X) const;
    virtual bool insert(const Key&X);
    void print();
    
  private:
    std::vector<Key> self;

};

#endif