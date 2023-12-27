#if !defined(ITEMS_H_INCLUDED)
#define ITEMS_H_INCLUDED

#include <string>
using namespace std;

class item{
  int id;
  string name;
  string description;
  string consume_type;
  int max_stack;
  int stack;
  int price;
  bool instanced;
  
  public:
    int get_id();
    string get_name();
    string get_description();
    string get_consume_type();
    int get_max_stack();
    int get_stack();
    int get_price();
    bool is_instanced();
    void use();

};
class weapon:public item{};
class armor:public item{};

#endif // ITEM_H_INCLUDED
