#include "structure.h"
using namespace std;


//print the map
void Map::print_map(Player player){
    Point p = player.position;
    string player_image[RANGE_X];
    player_image[0]="  o ";
    player_image[1]=" <|>";
    player_image[2]="  ^ ";
    for(int i = 0; i < len_x; i++)
    for(int _i = 0; _i < RANGE_X; _i++){         //i-th row of the map
        string s = "\u25BC";
        for(int j = 0; j < len_y; j++) //j-th column of the map
            if(p.x==i && p.y==j)
                s += player_image[_i];
            else 
                s += map[i][j].image.s[_i]; 
        s += " \u25BC";
        if(i == 0 && _i == 1){
            if (player.if_protect==true)
                s += "[Using] \033[34m\u25C6\033[0m Shield(press 'j'): "+to_string(player.package[1].num);
            else
                s += "     \033[34m\u25C6\033[0m Shield(press 'j'): "+to_string(player.package[1].num);

        }
            
        if(i == 1 && _i == 0)
            s += "     \u2605 Spring(press 'k'): "+to_string(player.package[2].num);
        if(i == 1 && _i == 2) 
            s += "     \033[32m。\033[0mSeed(press 'l'): "+to_string(player.package[3].num);
        if(i == 2 && _i == 1)
            s += "     {\u2739} Bomb(press 'b'): no limit";
        cout << s << endl;
    }
    
}

void Map::build_map(int _level, int _){
    level = _level;
    len_x = maps_size[level][_][0];
    len_y = maps_size[level][_][1];
    coins_need = maps_coin[level][_];


    map = new unit *[len_x];
    
    for(int i = 0; i < len_x; i++)
        map[i] = new unit [len_y];

    for(int i = 0; i < len_x; i++){
        for(int j = 0; j < len_y; j++){     //build map[i][j]

            char c = maps[level][_][i][j]; 
            if(c == 'S')
                map[i][j].set("space", i, j);
            else if (c == 'W')
                map[i][j].set("wall", i, j);
            else if (c == 'B')
                map[i][j].set("box", i, j);
        }
    }
}

void Map::delete_map(){
    for(int i = 0; i < len_x; i ++){
        for(int j = 0; j < len_y; j ++){
            if (map[i][j].prop!=NULL){
                delete map[i][j].prop;
                map[i][j].prop = NULL;
            }
            if (map[i][j].bomb!=NULL){
                delete map[i][j].bomb;
                map[i][j].bomb = NULL;
            }
            if (map[i][j].box!=NULL){
                delete map[i][j].box;
                map[i][j].box = NULL;
            }  

        }
    }
    for(int i = 0; i < len_x; i ++){
        delete[] map[i];
        map[i] = NULL;
    }
    delete[] map;
    map = NULL;
}

//set a bomb
//input: the position of the bomb
void Map::set_bomb(Point p, Time t){
    map[p.x][p.y].set("bomb", p.x, p.y);
    map[p.x][p.y].bomb = new Bomb;
    map[p.x][p.y].bomb-> set_time.set(t.min, t.sec);
}

//set a seed
//input: the position of the seed
void Map::set_seed(Point p, Time t){
    map[p.x][p.y].set("box", p.x, p.y);
    map[p.x][p.y].box-> set_time = t;
    map[p.x][p.y].box-> if_box = false;
    map[p.x][p.y].image.seed_used();
}