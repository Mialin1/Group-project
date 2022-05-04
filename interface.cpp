#include <iostream>
#include "interface.h"
#include "structure.h"
#include "IO.h"
using namespace std;

//all the pages are printed by this function
void print_page(){

}

//functions below are page generator
//maybe use a string array to store the page to be printed

//a page with welcome information
void welcome_page(Player *player){
    
    //Your name is: 
    //ask player to input their name
    print_page();


    player -> name = "NAME";

    //a new page:
    //Nice to meet you, XXX
    //list out the rule of the game
    print_page();

    //press space/enter to quit welcome__page
    print_page();

};  

void room_page(Player *player){
    //if there is any, ask user if he/she want to load previously archieved game
    //yes(y)      no(n)
    print_page();
    //if yes, load the previous map(map.readmap()), and quit room_page
    //maybe a loading page
    for(int i = 0; i < 10; i ++){
        //generate the loading bar by time
        print_page();
    }


    //list out all the maps for users to choose
    //higher level map may be locked, the locked map should be gray
    print_page();

    //player->map = ;
    //press ____ to choose the map and quit room_page
}

void game_page(Player player){

    //player: Player_Name
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
    // time remaining:    03: 00

    //maybe also use struct func (map.print_map())
    //or turn the struct func to a generator and also use the print_page() functoin
    print_page();
    
    
}

void quit_page(){
    //See you next time
    print_page();
}

void check_page(Player *player){
    //are you sure to leave
    //yes(y)            no(n)
    print_page();

    char x = get_input();
    if (x =='y') player -> if_quit = true;

    //new page
    //Do you want to archive your status?
    //yes(y)            no(n)
    print_page();
    
    x = get_input();
    if (x == 'y'){
        //save the status to file
        //status: Profile and Map
    }

    //newpage
    //The status is succesfully saved
    print_page();
}

bool quit_game(Player player){
    return player.if_quit;
}

void warning(){
    //invalid move/operation
}