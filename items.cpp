#include "h_files/items.h"
#include <iostream>
using namespace std;

int item::get_id(){
  return id;
}
string item::get_name(){
  return name;
}
string item::get_description(){
  return description;
}
string item::get_consume_type(){
  return consume_type;
}
int item::get_max_stack(){
  return max_stack;
}
int item::get_stack(){
  return stack;
}
int item::get_price(){
  return price;
}
bool item::is_instanced(){
  return instanced;
}
void item::use(){
  cout << "no use till now!" << endl;
}