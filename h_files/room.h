#if !defined(ROOM_H_INCLUDED)
#define ROOM_H_INCLUDED

#include "entities.h"
#include "player.h"
#include <string>
#include <vector>
using namespace std;

class room{
  int id;
  bool locked;
  int requirement;
  string failed_requirement;
  int pos[2];
  vector<entity> entities;
  bool connects[4];
  bool placeholder;
  vector<string> room_structure;
  bool active;
  bool exit;

public:
  void init(int rid, bool lock, int req, string failed, int pos[2], vector<entity> entities,bool connections[4], bool placeholder,bool is_active);
  bool is_exit();
  void make_exit();
  int get_id();
  bool is_locked();
  int get_requirement();
  string get_failed_requirement();
  int* get_pos();
  bool is_placeholder();
  void unlock(player &play);
  void remove_placeholder();
  void change_connection(int direction);
  void build_room();
  bool* get_connections();
  vector<string> get_structure();
  void change_active();
  bool is_active();
};

#endif // ROOM_H_INCLUDED
