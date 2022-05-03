#include "structure.h"
#include "interface.h"
#include "IO.h"
#include <cstdio>
#include <iostream>
#include <ctime>
#include <thread>

using namespace std;

int main(){

    Player player;

    player.initialize();
    
    welcome_page(&player); 
    
    //for player to choose room
    room_page(&player);

    game_page(player);

    char x;//the input from the user
    
    while(1){       //refresh the interface when get a command or time refresh

        if (quit_game(player)){
            quit_page();
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
                    
                    int _ = get_input() - '0';
                    if(_ == 1){                 //use a shield
                        player.use_shield();
                    }

                    if(_ == 2){                 //use a spring
                        int __ = get_input();   //the direction he face
                        int _x, _y = 0;
                        if (__ == 'W')  _x = 0,  _y = -2;
                        if (__ == 'S')  _x = 0,  _y = 2;
                        if (__ == 'A')  _x = -2, _y = 0;
                        if (__ == 'D')  _x = 2,  _y = 0;
                        if (!player.jump(_x, _y))
                            warning();
                    }

                    if(_ == 3){                 //use a seed
                        if (!player.use_seed())
                            warning();
                    }
                case ' ': //user set bomb
                    if(!player.set_bomb())
                        warning();
                case 'Q': //quit game
                    check_page(&player);
                    //check if sure to quit the game
                    //if yes: player.if_quit = true

            }
        }
        
    }
}
