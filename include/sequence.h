#ifndef __SEQUENCE__
#define __SEQUENCE__

#include <vector>
#include <array>
#include <list>
#include <iostream>
 
template <class Key>
class Sequence{

  public:
    Sequence(const int Size = 0){}
    ~Sequence(void){}

    virtual bool search(const Key& X) const = 0;
    virtual bool insert(const Key&X) = 0;
};

#endif