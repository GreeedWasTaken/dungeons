#include "h_files/world.h"
#include "h_files/room.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

// container to randomly get t/f
bool bools[2] = {true, false};
int diff[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};


int randnum(int lb,int ub){
  return (rand() % (ub - lb + 1)) + lb;
}

// this function is used to initialize the world. it sets the seed for random number gen, initializes the room ids, calls the function for world generation and then displays the world map
void world::init(){
  srand(time(0));
  rooms = 0;
  gen_dungeon();
  // find random room and make it active room and start mapping from there.select active room
  int active_room_id = randnum(1, rooms);
  bool got_active = false;
  for (int floors = 0; floors < world_container.size();floors++){
    if(got_active == true){
      break;
    }
    for (int room = 0;room<world_container[floors].size();room++){
      if(world_container[floors][room].get_id() == active_room_id){
        active_room = world_container[floors][room];
        world_container[floors][room].change_active();
        got_active = true;
        break;
      }
    }
  }
  // start mapping the dungeon
  map_rooms(active_room.get_pos());

  assign_exit();

  show_map();
  change_active_room(active_room_id);
}

void world::assign_exit(){
  for(vector<room> floor:world_container){
    for(room r:floor){
      if(r.is_placeholder() == false){
        if(bools[randnum(0,1)]){
          r.make_exit();
          int* pos = r.get_pos();
          exit = world_container[pos[0]][pos[1]];
        }
      }
    }
  }
}

void world::change_active_room(int roomID){
  for (int floor = 0; floor < world_container.size();floor++){
    for (int room_num = 0;room_num<world_container[floor].size();room_num++){
      if(world_container[floor][room_num].get_id() == roomID){
        int* pos = active_room.get_pos();
        world_container[pos[0]][pos[1]].change_active();
        world_container[pos[0]][pos[1]].build_room();
        active_room = world_container[floor][room_num];
        world_container[floor][room_num].change_active();
        world_container[floor][room_num].build_room();
        return;
      }
    }
  }
}

void world::show_map(){
  vector<vector<string>> floor;
  int size_of_room = active_room.get_structure().size();
  for (int i = 0; i < size_of_room;i++){
    vector<string> part;
    floor.push_back(part);
  }

  // floor: {{string1,string2},{},{},{},{},{}}
  // floor[0][1] = string1
  // parts: {string1,string2}
  // parts[0] = string1
  for (int floors = 0; floors < world_container.size();floors++){
    for (room r:world_container[floors]){
      vector<string> parts = r.get_structure();
      for (int i = 0; i < size_of_room;i++){
        floor[i].push_back(parts[i]);
      }
    }
    for (int levels = 0; levels < size_of_room;levels++){
      for (int parts = 0; parts < floor[levels].size();parts++){
        cout << floor[levels][parts];
      }
      cout << endl;
      floor[levels].clear();
    }
  }
}

void world::map_rooms(int pos[2]){
  room &room_being_mapped = world_container[pos[0]][pos[1]];
  room_being_mapped.remove_placeholder();
  room_being_mapped.build_room();
  active_rooms_per_floor[pos[0]] += 1;
  vector<int> active_room_pos;
  active_room_pos.push_back(room_being_mapped.get_pos()[0]);
  active_room_pos.push_back(room_being_mapped.get_pos()[1]);
  active_rooms.push_back(active_room_pos);

  bool up_is_open = pos[0] - 1 >= 0;
  bool right_is_open = pos[1] + 1 < world_container[pos[0]].size();
  bool down_is_open = pos[0] + 1 < world_container.size();
  bool left_is_open = pos[1] - 1 >= 0;
  bool options[4] = {up_is_open,right_is_open,down_is_open, left_is_open};
  bool* cur_con = room_being_mapped.get_connections();

  for (int i = 0; i < 4;i++){
    bool change;
    if(cur_con[i]==false){
      change = bools[randnum(0, 1)];
    }else{
      change = false;
      break;
    }
    if(options[i] == true && change == true){

      // get next room pos
      int next_room_pos[2] = {pos[0] + diff[i][0], pos[1] + diff[i][1]};

      // check if the max active rooms have been reached in the floor of the next room. check if the room is already connected. if any of it it true then do not map room.
      room &next_room = world_container[next_room_pos[0]][next_room_pos[1]];
      int dir;
      if(i < 2){
        dir = i + 2;
      }else{
        dir = i - 2;
      }
      if((active_rooms_per_floor[next_room_pos[0]] < accessible_rooms_per_floor[next_room_pos[0]] == true) && (next_room.get_connections()[dir] == false)){
        room_being_mapped.change_connection(i);
        next_room.change_connection(dir);
        map_rooms(next_room_pos);
      }
      room_being_mapped.build_room();
    }
  }
}

void world::gen_dungeon(){
  // decide how many floors this dungeon should have
  int floors = randnum(1, 5);
  vector<room> floor;
  // add empty floors to world container
  for (int i = 0; i < floors;i++){
    for (int j = 0; j < 6; j++)
    {
      // what will be inside the room? chest? monster?
      vector<entity> t;

      // pos of the room
      int pos[2] = {i, j};

      // if the room requires something for entry
      bool is_locked = bools[randnum(0, 1)];

      // to which directions the room has exits towards (up,left,down,right)
      bool connections[4] = {false,false,false,false};

      // if the room is empty and inaccessible basically void
      bool placeholder = true;

      // create room object and add it to the floor
      room r;
      r.init(rooms, is_locked, 0, " ", pos, t,connections,placeholder,false);
      floor.push_back(r);

      // keep track of how many rooms in the world
      rooms += 1;
    }
    world_container.push_back(floor);
    active_rooms_per_floor.push_back(0);
    floor.clear();
    accessible_rooms_per_floor.push_back(randnum(1, 6));
  }
}

bool* world::rooms_player_can_enter(){
  return active_room.get_connections();
}

int world::get_room_id(int pos[2]){
  return world_container[pos[0]][pos[1]].get_id();
}

int* world::get_active_room_pos(){
  return active_room.get_pos();
}

bool world::is_exit(int pos[2]){
  return exit.get_pos()[0] == pos[0] && exit.get_pos()[1] == pos[1];
}