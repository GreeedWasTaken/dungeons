#if !defined(PLAYER_H_INCLUDED)
#define PLAYER_H_INCLUDED

#include <vector>
#include <map>
#include "items.h"

class player{
  //stats
  int health;
  int armor;
  int mana;
  int strength;
  int agility;
  int dexterity;

  //inv
  map<int,item> inventory;

  //equipped items
  item head;
  item chest;
  item main_hand;
  item off_hand;
  item gloves;
  item legs;
  item boots;

  public:
    bool has_item(int id);
    void use_item(int id);
};

#endif // PLAYER_H_INCLUDED
