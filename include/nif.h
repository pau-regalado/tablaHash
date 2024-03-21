#include <iostream>
#include <cstdlib>

class Nif {
private:
  long num;

public:
  Nif() { num = generarAleatorio(); }

  Nif(long num) { this->num = num; }

  long getNum() const { return num; }
  void setNum(long num) { this->num = num; }

  long generarAleatorio() { return rand() % 100000000; }

  bool operator==(const Nif& otro) const { return num == otro.num; }
  Nif& operator=(const Nif& otro) {
    this->setNum(otro.getNum());
    return *this;
  }

  operator long() const { return num; }
  operator int() const { return num; }

  friend std::ostream& operator<<(std::ostream& os, Nif& nif) {
    os << nif.getNum();
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Nif& nif) {
    long num;
    is >> num;
    nif.setNum(num);
    return is;
  }
};