#include <iostream>
#include "interface.h"
#include "structure.h"
#include "IO.h"
using namespace std;

//a page with welcome information
void welcome_page(Player *player){
    
    //Your name is: 
    //ask player to input their name


    player -> setname("name");

    //a new page:
    //Nice to meet you, XXX
    //list out the rule of the game

    //press space/enter to quit welcome__page
};  

void room_page(Player *player){
    //list out all the maps for users to choose
    //higher level map may be locked, the locked map should be gray

    //player->map = ;
    //press ____ to choose the map and quit room_page
}

void game_page(Player player){

    //我觉得大致长这样

    //level: 1
    // -------------------------
    //|                         |
    //|                         |
    //|                         |
    //|                         |
    //|                         |
    //|                         |
    //|                         |
    //|                         |
    //|                         |
    // -------------------------
    // life: 1    coin(s): 0/100
    // time remaining: 03: 00


}

void quit_page(){
    //See you next time
}

void check_page(Player *player){
    //are you sure to leave
    //yes(y)            no(n)
    char x = get_input();
    if (x=='y') player -> if_quit = true;
}



bool quit_game(Player player){
    return player.if_quit;
}
