#include <iostream>
#include <ctime>
#include "map_update.h"
#include "interface.h"
#include "structure.h"
using namespace std;

//update the screen per_sec
void map_update(Player *player){
    game_page(*player);

    // usleep(1000);       hang the thread up for 1 sec
    // time_remaining --

    Map *map = player->map;

    for(int i = 0; i < map->len_x; i ++){
        for(int j = 0; j < map->len_y; j ++){
            unit u = map -> map[i][j]; 
            
            //check if there is any bomb to bang

            //check if there is any shield
            
        }
    }
}