#include <iostream>
#include <string>
#include "h_files/world.h"
#include <vector>
using namespace std;

void clear(){
  cout << string(1024, '\n');
}

int main(){
  world world_container;
  world_container.init();
  int ch;
  while(true){
    int ch;
    cout << "1) move to next room \nEnter your choice: ";
    cin >> ch;
    if(ch==1){
      bool *connects = world_container.rooms_player_can_enter();
      int dirs = 0;
      for (int i = 0; i < 4;i++){
        if(connects[i]==true){
          dirs += 1;
        }
      }
      vector<vector<int>> choices;
      int *pos = world_container.get_active_room_pos();
      int diff[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
      for (int i = 0; i < 4;i++){
        if(connects[i]==true){
          choices.push_back({pos[0] + diff[i][0],pos[1] + diff[i][1]});
          cout << choices.size();
          if(i==0){
            cout << ") go up" << endl;
          }else if(i==1){
            cout << ") go right" << endl;
          }else if(i==2){
            cout << ") go down" << endl;
          }else if(i==3){
            cout << ") go left" << endl;
          }
        }
      }
      if(world_container.is_exit(world_container.get_active_room_pos()) == true){
        cout << choices.size() + 1 << ") exit" << endl;
      }
      cout <<"Enter your choice: ";
      cin >> ch;
      while(true){
        if(ch < 1 || ch > choices.size()+1){
          cout << "invalid input! try again! \nEnter your choice: ";
          cin >> ch;
        }else{
          break;
        }
      }
      if(ch == choices.size() + 1){
        cout << "thanks for playing!" << endl;
        break;
      }
      int new_pos[2] = {choices[ch-1][0], choices[ch-1][1]};
      world_container.change_active_room(world_container.get_room_id(new_pos));
      world_container.show_map();
    }else if(ch==2){
      cout << "thanks for playing!" << endl;
      break;
    }else{
      cout << "invalid input!" << endl;
    }
  }
}