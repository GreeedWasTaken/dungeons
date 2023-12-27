#if !defined(INVENTORY_H_INCLUDED)
#define INVENTORY_H_INCLUDED

#include "items.h"
#include <map>

class inventory{
  map<int,item> inv;
  int currency;

  public:
    void spend(int x);
    bool afforable(int x);
};

#endif // INVENTORY_H_INCLUDED
