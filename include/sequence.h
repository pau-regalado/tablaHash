#ifndef __SEQUENCE__
#define __SEQUENCE__
 
template <class Key>
class Sequence{
  public:
    virtual bool search(const Key& X) const = 0;
    virtual bool insert(const Key&X) = 0;
    virtual bool isFull(void) const = 0;
    virtual void print() = 0;
};

#endif