#include <iostream>
#include <cstdlib>

class Nif {
private:
  long num;

public:
  Nif() { num = generarAleatorio(); }

  Nif(long num) { this->num = num; }

  long generarAleatorio() { return rand() % 100000000; }

  bool operator==(const Nif& otro) const { return num == otro.num; }

  operator long() const { return num; }
};