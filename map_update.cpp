#include <iostream>
#include <ctime>
#include "map_update.h"
#include "interface.h"
#include "structure.h"
using namespace std;

//time structure for countdown
struct Time{
    int min;
    int sec;

    //set the time structure
    void set(int _m, int _s){
        min = _m;
        sec = _s;
    }
    
    //calculate the time span between itself and the input time
    //tip: input time is smaller
    Time diff(Time _time){
        Time diff;
        if (sec < _time.sec)
            sec += 60, min -= 1;
        diff.set(min - _time.min, sec - _time.sec);
        return diff;
    }

    //time goes down for 1 sec
    void tick(){
        if (sec == 0)
            sec = 60, min -= 1;

        sec --;
    }

    bool if_over(){
        return(min == 0 && sec == 0);
    }

    bool bomb_span(){
        if(min == 0 && sec == 15)   //set a bomb every 15s
            return true;
        return false;
    }
};

//update the screen per_sec
void map_update(Player *player){

    Time remain;
    remain.set(5, 0);        //e.g. 5 mins per round

    Time last_bomb = remain;

    game_page(*player);

    while(1){
        // usleep(1000);       hang the thread up for 1 sec
        remain.tick();  //minus 1 sec

        Map *map = player->map;

        //every few seconds drop a bomb randomly
        if (last_bomb.diff(remain).bomb_span()){
            //randomly pick an empty unit and place a bomb
            //the bomb will be explode in 1 sec
        }

        for(int i = 0; i < map->len_x; i ++){
            for(int j = 0; j < map->len_y; j ++){
                unit u = map -> map[i][j]; 
            
                //check if there is any bomb to bang
                //release the dynamic memory after explosion

                //check if there is any shield expire

                //check for tree growing(seed->tree->wooden boxes)
            
            }
        }
    }
    
    
}