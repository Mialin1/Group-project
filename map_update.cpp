#include <iostream>
#include <ctime>
#include "map_update.h"
#include "interface.h"
#include "structure.h"
#include "IO.h"
using namespace std;

//update the screen per_sec
void map_update(Player *player){
    
    player -> time_remain.set(5, 0);        //e.g. 5 mins per round

    Time last_bomb = player -> time_remain;

    game_page(*player);

    srand(player->time_remain.sec);


    while(1){
        //1 sec
        struct timespec ts, ts1;
        ts.tv_nsec = 0;
        ts.tv_sec = 1;
        nanosleep(&ts, &ts1);

        player -> time_remain.tick();  //minus 1 sec

        Map *map = player->map;

        Time remain = player -> time_remain;

        //every few seconds drop a bomb randomly
        if (last_bomb.diff(remain).bomb_span()){
            Point bomb;
            //randomly pick an empty unit and place a bomb
            unit *u = map->empty[rand() % map->empty.size()];
            map->set_bomb(u->position, remain);
            //the bomb will be explode in 1 sec
        }

        //check if there is any shield expire
        if (player -> time_protect.diff(remain).shield_up()){
            player -> if_protect = false;
        }

        //check for map units changes
        for(int i = 0; i < map->len_x; i ++){
            for(int j = 0; j < map->len_y; j ++){
                unit u = map -> map[i][j]; 
            
                //check if there is any bomb to bang
                //can add explosion effect here
                if (u.bomb != NULL){
                    //effect1
                    if(u.bomb -> effect1(remain)){}
                    //effect2
                    if(u.bomb -> effect2(remain)){}

                    //time to explode
                    if(u.bomb -> explode(remain)){
                        //3*3 all to empty(except for stone walls)
                        //boxes became coins / props
                        for(int _i = max(0, i-1); _i <= min(RANGE_X, i+1); _i ++)
                            for(int _j = max(0, j-1); _j <= min(RANGE_Y, j+1); _j ++){
                                unit u1 = map -> map[_i][_j];

                                //check if user is in this zone
                                if (player -> position.x == _i && player -> position.y == _j){
                                    player -> life --;
                                    if (player -> life == 0){
                                        dead(*player);
                                        if(get_input()){
                                            check_page(*player);

                                            if(player->if_quit) //if player has quit the game
                                                return;
                                            
                                        }
                                            
                                    }
                                        
                                }
                                //destroy all the breakables
                                
                                
                                //break the boxes and release the random coins/porps
                            }
                        
                        
                    }

                    //effect3
                    //effect4

                    //release dynamic memory
                    if(u.bomb -> release(remain))
                        delete u.bomb;

                }


                //check for tree growing(seed->tree->wooden boxes)
                if (u.tree != NULL){
                    if(u.tree -> to_tree(remain)){
                        //the image of this unit turn into tree
                    }
                    else if(u.tree -> to_box(remain)){
                        //the image turn into tree
                    }
                }
            
            }
        }
    }
    
    
}