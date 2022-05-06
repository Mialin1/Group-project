#include "structure.h"
using namespace std;

//print the map
void Map::print_map(Point position){
    string player_image[RANGE_X];
    player_image[0]=" o ";
    player_image[1]="<|>";
    player_image[2]=" ^ ";
    for(int i = 0; i < len_x; i++){         //i-th row of the map
        for(int _i = 0; _i < RANGE_X; _i++)
        for(int j = 0; j < len_y; j++) //j-th column of the map
        for(int _j = 0; _j < RANGE_Y; _j++){
            if(position.x==i && position.y==j){
                if(j==0){
                    cout << "\u25B2 "<<player_image[_i][_j];    
                }
                else if(j==(len_y-1)){
                    cout << player_image[_i][_j]<<" \u25BC"; 
                }
                else
                    cout << player_image[_i][_j];

            }
            else{
                if(j==0){
                    cout << "\u25B2 "<<map[i][j].image.s[_i][_j];    
                }
                else if(j==(len_y-1)){
                    cout << map[i][j].image.s[_i][_j]<<" \u25BC"; 
                }
                else
                    cout << map[i][j].image.s[_i][_j]; 
            }
        }
        cout << endl;
    }
    
}

void Map::delete_map(){
    for(int i = 0; i < len_x; i ++)
        delete map[i];
    delete *map;
}

//set a bomb
//input: the position of the bomb
void Map::set_bomb(Point p, Time t){
    map[p.x][p.y].bomb = new Bomb;
    map[p.x][p.y].bomb-> set_time = t;
    map[p.x][p.y].empty = false;
    map[p.x][p.y].image.set_bomb();
}

//set a seed
//input: the position of the seed
void Map::set_seed(Point p, Time t){
    map[p.x][p.y].box = new Box;
    map[p.x][p.y].bomb-> set_time = t;
    map[p.x][p.y].empty = false;
}