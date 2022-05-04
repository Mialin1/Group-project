#include <iostream>
#include <ctime>
#include "map_update.h"
#include "interface.h"
#include "structure.h"
using namespace std;

//update the screen per_sec
void map_update(Player *player){
    
    player -> time_remain.set(5, 0);        //e.g. 5 mins per round

    Time last_bomb = player -> time_remain;

    game_page(*player);

    while(1){
        //1 sec
        struct timespec ts, ts1;
        ts.tv_nsec = 0;
        ts.tv_sec = 1;
        nanosleep(&ts, &ts1);

        player -> time_remain.tick();  //minus 1 sec

        Map *map = player->map;

        //every few seconds drop a bomb randomly
        if (last_bomb.diff(player -> time_remain).bomb_span()){
            Point bomb;
            //randomly pick an empty unit and place a bomb
            //the bomb will be explode in 1 sec
        }

        //check if there is any shield expire
        if (player -> time_protect.diff( player->time_remain).shield_up()){
            player -> if_protect = false;
        }

        //check for map units changes
        for(int i = 0; i < map->len_x; i ++){
            for(int j = 0; j < map->len_y; j ++){
                unit u = map -> map[i][j]; 
            
                //check if there is any bomb to bang
                //release the dynamic memory after explosion
                if (u.bomb != NULL){

                }
                //check for tree growing(seed->tree->wooden boxes)
                
            
            }
        }
    }
    
    
}