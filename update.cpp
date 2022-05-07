#include "update.h"
#include "interface.h"
#include "structure.h"
#include "IO.h"
using namespace std;

//update the screen per_sec
void map_update(Player &player){

    Time last_bomb = player.time_remain;


    srand(time(0));

    while(true){
        //1 sec
        struct timespec ts, ts1;
        ts.tv_nsec = 0;
        ts.tv_sec = 1;
        nanosleep(&ts, &ts1);

        player.time_remain.tick();  //minus 1 sec
        Map *map = player.map;

        if(player.time_remain.if_time_up()){
            check_page(player);
            map->delete_map();
            delete map;
            map = NULL;
            room_page(player);
            last_bomb = player.time_remain;
        }

        Time remain = player.time_remain;

        //every few seconds drop a bomb randomly
        if (last_bomb.diff(remain).bomb_span(player.map->level)){
            Point bomb;
            //randomly pick an empty unit and place a bomb
            Point p;
            p.set(rand()% player.map->len_x, rand()% player.map->len_y);
            while(!map->map[p.x][p.y].empty || (p.x == player.position.x && p.y == player.position.y)){
                p.set(rand()% player.map->len_x, rand()% player.map->len_y);
            }

            map->set_bomb(p, remain);
            last_bomb = remain;
            //the bomb will be explode in 1 sec
        }

        //check if there is any shield expire
        if (player.time_protect.diff(remain).shield_up()){
            player.if_protect = false;
        }
        
        bool restart = false;

        //check for map units changes
        for(int i = 0; i < map->len_x; i ++){
            for(int j = 0; j < map->len_y; j ++){
                unit &u = map -> map[i][j]; 
            
                //check if there is any bomb to bang
                //can add explosion effect here
                if (u.bomb != NULL){
                    //effect1
                    if(u.bomb -> effect1(remain)){  //1sec
                        map -> map[i][j].image.s[0] = " \033[31m - \033[0m";
                        map -> map[i][j].image.s[1] = "  \033[31m\u2739\033[0m ";
                        map -> map[i][j].image.s[2] = " \033[31m - \033[0m";
                    }
                    //effect2
                    if(u.bomb -> effect2(remain)){
                        for(int _i = max(0, i-1); _i < min(map->len_x, i+2); _i ++){
                            for(int _j = max(0, j-1); _j < min(map -> len_y, j+2); _j ++){

                                unit &u1 = map -> map[_i][_j];

                                u1.image.s[0]="\033[45m"+u1.image.s[0]+"\033[0m";
                                u1.image.s[1]="\033[45m"+u1.image.s[1]+"\033[0m";
                                u1.image.s[2]="\033[45m"+u1.image.s[2]+"\033[0m";
                            }
                        }
                    }

                    //the moment after explosion(the outcome)
                    if(u.bomb -> explode(remain)){
                        //3*3 all to empty(except for stone walls)
                        //boxes became coins / props
                        for(int _i = max(0, i-1); _i < min(map->len_x, i+2); _i ++){
                            for(int _j = max(0, j-1); _j < min(map -> len_y, j+2); _j ++){
                                
                                unit &u1 = map -> map[_i][_j];

                                //check if user is in this zone
                                if (player.position.x == _i && player.position.y == _j){
                                    //if player is not protected, life --
                                    if(!player.if_protect){
                                        player.life --;

                                        if (player.life == 0){
                                            dead(player);
                                            restart = true;
                                            break;
                                        }
                                    }   
                                }
                                //destroy all the breakables
                                else if(u1.breakable){ 
                                    //break the boxes and release the random coins/porps
                                    if(u1.box != NULL && u1.box->if_box ){
                                        //0 heart, 1 shield, 2 spring, 3 seed
                                        //4 to 9, (_ - 3)coins
                                        int _ = rand()%15; 
                                        if(_ < 4){
                                            u1.set("prop", _i, _j);
                                            u1.prop = new Prop;
                                            u1.prop -> set(_, 1);
                                            if(_ == 0) u1.image.set_heart();
                                            if(_ == 1) u1.image.set_shield();
                                            if(_ == 2) u1.image.set_spring();
                                            if(_ == 3) u1.image.set_seed();
                                        }
                                        else if(_ < 10){
                                            u1.set("prop", _i, _j);
                                            u1.prop = new Prop;
                                            u1.prop->set(_, _ - 3);
                                            u1.image.set_coin();
                                        }

                                    }
                                    //other things -> space
                                    else{
                                        u1.set("space", _i, _j); //set to space
                                    }
                                }
                                else{
                                    u1.image.s[0]=u1.image.s[0].substr(5, 4);
                                    u1.image.s[1]=u1.image.s[1].substr(5, 4);
                                    u1.image.s[2]=u1.image.s[2].substr(5, 4);
                                }
                            }
                            if (restart) break;
                        }
                        u.set("space", i, j);
                        delete u.bomb;
                        u.bomb = NULL;
                        if (restart) break;
                    }
                    
                }

                //check for seed growing(seed->wooden boxes)
                if (u.box != NULL && !u.box->if_box){
                    if(u.box -> to_box(remain)){
                        u.box->if_box = true;
                        u.image.set_box();
                    }
                }
            
            }
            if (restart) break;
        }

        if(restart){
            map->delete_map();
            delete map;
            map = NULL;
            room_page(player);
            last_bomb = player.time_remain;
            restart = false;
            continue;
        }

        game_page(player);//print the page after update
    }
    
    
}