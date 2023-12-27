#include "h_files/player.h"
#include "h_files/items.h"

bool player::has_item(int id){
  if(inventory.count(id) == 1){
    return true;
  }else{
    return false;
  }
}

void player::use_item(int id){
  inventory[id].use();
}