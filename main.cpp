/*
 * @Author: HuangLeyang
 * @since: 2022-04-30 11:42:31
 * @lastTime: 2022-04-30 13:18:22
 * @message: This author is asomething blablablabla

 */
#include "structure.h"
#include "interface.h"
#include "IO.h"
#include<cstdio>
#include<iostream>
#include<chrono>
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
                    x = get_input();
                case 'Q': //quit game
                    check_page(&player);
                    //check if sure to quit the game
                    //if yes: player.if_quit = true

            }
        }
        
    }
}
