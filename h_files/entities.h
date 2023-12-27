#if !defined(ENTITIES_H_INCLUDED)
#define ENTITIES_H_INCLUDED

class entity{
  int health;
  int armor;
  int damage;
};

class container:public entity{
};
class NPC:public entity{
};
class monster:public entity{
};

#endif // ENTITIES_H_INCLUDED
