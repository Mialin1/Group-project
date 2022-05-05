#include "structure.h"
#include "interface.h"
#include "map_update.h"
#include "IO.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>

using namespace std;
<<<<<<< HEAD
extern vector<vector<Map> > maps;
=======

extern vector<vector<Map>> maps;

>>>>>>> c0042af0ba7b83fed448841e5d54180ef8c5f157
int main(){

    Player player;

    input_maps();

    player.initialize();
    
    welcome_page(&player); 
    
    //for player to choose room
    room_page(&player);

    //one more thread to update the screen per_sec no matter the player moves or not
    thread update (map_update, &player);
    update.detach();

    char x;//the input from the user
    while(1){       //refresh the interface when get a command or time refresh

        if (player.if_quit){
            quit_page();
            break;
        }
        else {
            x = get_input();

            switch(x){
                case 'W': //move upward
                    player.move(0, -1);
                case 'S': //move downward
                    player.move(0, 1);
                case 'A': //move leftward
                    player.move(-1, 0);
                case 'D': //move rightward
                    player.move(1, 0);
                case 's': //uses props
                    
                    int _x = get_input(), _;
                    if (_x == 'J') _ = 0;
                    if (_x == 'K') _ = 1;
                    if (_x == 'L') _ = 2;

                    if (player.package[_].num == 0)
                        warning();
                    else if(_ == 0){                 //use a shield
                        player.use_shield();
                    }
                    else if(_ == 1){                 //use a spring
                        int __ = get_input();   //the direction he face
                        int _x, _y = 0;
                        if (__ == 'W')  _x = 0,  _y = -2;
                        if (__ == 'S')  _x = 0,  _y = 2;
                        if (__ == 'A')  _x = -2, _y = 0;
                        if (__ == 'D')  _x = 2,  _y = 0;
                        if (!player.jump(_x, _y))
                            warning();
                    }
                    else if(_ == 2){                 //use a seed
                        player.use_seed();
                    }
                case ' ': //user set bomb
                    if(!player.set_bomb())
                        warning();

                case 'Q': //quit game
                    leave_page(&player);

            }
        }
        
    }
}
