#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <string>
#include "room.h"
#include "player.h"
#include "entities.h"

// needs to have a map
// change active room
// player object

class world{
  vector<vector<room>> world_container;
  vector<int> accessible_rooms_per_floor;
  vector<int> active_rooms_per_floor;
  vector<vector<int>> active_rooms;
  room active_room;
  player player_object;
  int rooms;
  room exit;

public:
  // handles creation of the world
  void init();
  // roomID: room id of the room you want to make as the active room
  void change_active_room(int roomID);
  // shows map
  void show_map();
  // generate rooms
  void gen_dungeon();
  // returns the rooms the player can enter from the current room
  bool* rooms_player_can_enter();
  // handles the mapping of the dungeon.
  void map_rooms(int pos[2]);

  int get_room_id(int pos[2]);

  int *get_active_room_pos();

  bool is_exit(int pos[2]);

  void assign_exit();
};

#endif