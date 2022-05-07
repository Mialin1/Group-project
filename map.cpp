#include "structure.h"
using namespace std;

//print the map
void Map::print_map(Point position){
    string player_image[RANGE_X];
    player_image[0]=" o ";
    player_image[1]="<|>";
    player_image[2]=" ^ ";
    for(int i = 0; i < len_x; i++)
    for(int _i = 0; _i < RANGE_X; _i++){         //i-th row of the map
        cout << "\u25BC ";
        for(int j = 0; j < len_y; j++) 
        for(int _j = 0; _j < RANGE_Y; _j++){    //j-th column of the map
            if(position.x==i && position.y==j)
                cout << player_image[_i][_j];
            else 
                cout << map[i][j].image.s[_i][_j]; 
        }
        cout << " \u25BC" << endl;
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
        delete map[i];
        map[i] = NULL;
    }
    delete *map;
    *map = NULL;
}

//set a bomb
//input: the position of the bomb
void Map::set_bomb(Point p, Time t){
    map[p.x][p.y].bomb = new Bomb;
    map[p.x][p.y].bomb-> set_time = t;
    map[p.x][p.y].set("bomb", p.x, p.y);
}

//set a seed
//input: the position of the seed
void Map::set_seed(Point p, Time t){
    map[p.x][p.y].set("box", p.x, p.y);
    map[p.x][p.y].box-> set_time = t;
    map[p.x][p.y].box-> if_box = false;
    map[p.x][p.y].image.seed_used();
}