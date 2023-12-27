#if !defined(ROOM_H_INCLUDED)
#define ROOM_H_INCLUDED

#include "entities.h"
#include "player.h"
#include <string>
#include <vector>
using namespace std;

class room{
  bool locked;
  bool connects[4];
  bool placeholder;
  bool exit;
  bool active;

  int id;
  int requirement;
  int pos[2];

  string failed_requirement;
  
  vector<entity> entities;
  vector<string> room_structure;

public:
  void init(int rid, bool lock, int req, string failed, int pos[2], 
  
  vector<entity> entities,bool connections[4], bool placeholder,bool is_active);
  bool is_exit();
  bool is_locked();
  bool is_placeholder();
  bool* get_connections();
  bool is_active();
  bool is_empty();

  int get_id();
  int get_requirement();
  int* get_pos();

  string get_failed_requirement();

  vector<string> get_structure();
  vector<entity> get_entity_list();

  void make_exit();
  void unlock(player &play);
  void remove_placeholder();
  void change_connection(int direction);
  void build_room();
  void change_active();
};

#endif // ROOM_H_INCLUDED
