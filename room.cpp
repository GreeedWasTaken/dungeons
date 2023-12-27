#include "h_files/room.h"
#include "h_files/player.h"
#include "h_files/items.h"

#include <iostream>
using namespace std;

void room::init(int rid, bool lock, int req, string failed, int post[2], vector<entity> entities_list, bool connections[4], bool is_placeholder, bool is_active){
  id = rid;
  locked = lock;
  requirement = req;
  failed_requirement = failed;
  for (int i = 0; i < 4;i++){
    connects[i] = connections[i];
  }
  pos[0] = post[0];
  pos[1] = post[1];
  entities = entities_list;
  placeholder = is_placeholder;
  active = is_active;
  build_room();
}

bool is_exit(){
  return exit;
}

void room::make_exit(){
  exit = true;
}

int room::get_id(){
  return id;
}

bool room::is_locked(){
  return locked;
}

int room::get_requirement(){
  return requirement;
}

string room::get_failed_requirement(){
  return failed_requirement;
}

int* room::get_pos(){
  return pos;
}

bool room::is_placeholder(){
  return placeholder;
}

void room::unlock(player &play){
  //check if player has the requirement and unlock if they have it.
  item req;
  if(play.has_item(requirement)){
    play.use_item(requirement);
  }
}

void room::remove_placeholder(){
  placeholder = false;
}

void room::change_connection(int direction){
  if(connects[direction] == true){
    connects[direction] = false;
  }else{
    connects[direction] = true;
  }
}

void room::build_room(){
  room_structure.clear();

  if(is_placeholder() == true){
    for (int i = 0; i < 7;i++){
      room_structure.push_back("         ");
    }
    return;
  }

  string space="       ";
  // one mid has a length of 9
  string mid = "#" + space + "#";
  // mid now has 54 size exits will be on at the start and end - 1 of row indices 2 and 3.

  if (connects[0]){
    room_structure.push_back("###   ###");
  }else{
    room_structure.push_back("#########");
  }

  for (int i = 0; i < 5;i++){
    room_structure.push_back(mid);
  }
  if (connects[3]){
    room_structure[2][0] = ' ';
    room_structure[3][0] = ' ';
    room_structure[4][0] = ' ';
  }
  if(connects[1]){
    room_structure[2][room_structure[2].size() - 1] = ' ';
    room_structure[3][room_structure[3].size() - 1] = ' ';
    room_structure[4][room_structure[4].size() - 1] = ' ';
  }

  if (connects[2]){
    room_structure.push_back("###   ###");
  }else{
    room_structure.push_back("#########");
  }
  if(active == true){
    string &part = room_structure[room_structure.size() / 2];
    part[part.size() / 2] = 'p';
  }
  return;
}

bool* room::get_connections(){
  return connects;
}

vector<string> room::get_structure(){
  return room_structure;
}

void room::change_active(){
  if(active == true){
    active = false;
  }else{
    active = true;
  }
}

bool room::is_active(){
  return active;
}