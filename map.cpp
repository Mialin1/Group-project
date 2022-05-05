#include "structure.h"
using namespace std;

//read maps from file
void Map::read_map(){
    //cin << len_x << len_y;
    len_x = 100, len_y = 100;       
    map = new unit *[len_x];
    for(int i = 0; i < len_x; i++)
        map[i] = new unit [len_y];
        
    for(int i = 0; i < len_x; i++){
        for(int j = 0; j < len_y; j++){
            //input information of unit [i, j]
            int _;  //_ denotes what kind of unit it is
            cin >> _;
            map[i][j].set(_, i, j);

            //add the empty ones to the queue
            if (map[i][j].empty){
                unit *u = &map[i][j];
                Point p;
                p.set(i,j);
                empty.push_back(p);
            }

        }
    }
}

//print the map
void Map::print_map(){
    for(int i = 0; i < len_x; i++){         //i-th row of the map
    for(int _i = 0; _i < RANGE_X; _i++)
        for(int j = 0; j < len_y; j++) //j-th column of the map
        for(int _j = 0; _j < RANGE_Y; _j++){
            // cout << map[i][j].image[_i][_j]; 
        }
        // cout << endl;
    }
}

//set a bomb
//input: the position of the bomb
void Map::set_bomb(Point p, Time t){
    map[p.x][p.y].bomb = new Bomb;
    map[p.x][p.y].bomb-> set_time = t;
    map[p.x][p.y].empty = false;
}

//set a seed
//input: the position of the seed
void Map::set_seed(Point p, Time t){
    map[p.x][p.y].box = new Box;
    map[p.x][p.y].bomb-> set_time = t;
    map[p.x][p.y].empty = false;
}