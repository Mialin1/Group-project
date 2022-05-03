#ifndef STRUCTURE_H
#define STRUCTURE_H

#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<ctime>
using namespace std;

//a position on the 2D map
struct Point{
    int x, y;//coordinates

    //the function sets the Point to a new coordinates
    //input: new coordinates
    void set(int _x, int _y){
        x = _x;
        y = _y;
    }

    //the function makes a move
    //input: units that changes in x and y axis
    void move(int _x, int _y){
        x += _x;
        y += _y;
    }
};

//Bombs
struct Bomb{
    bool set;
    clock_t set_time; //the time when the bomb was setted
};

#define RANGE 3     //the size of each unit

//information of each unit on the map
struct unit{
    bool breakable;
    bool walkable;
    bool empty;
    
    Bomb *bomb;     //point to the bomb on this unit(if any)
    
    int prop;
    char image[RANGE][RANGE];
    
};

struct Map{
    unit ** map;
    int len_x, len_y;  //the size of the map

    //read maps from file
    void read_map(){
        //cin << len_x << len_y;
        len_x = 100, len_y = 100;       
        map = new unit *[len_x];
        for(int i = 0; i < len_x; i++)
            map[i] = new unit [len_y];
        
        for(int i = 0; i < len_x; i++){
            for(int j = 0; j < len_y; j++){
                //input information of unit [i, j]
            }
        }
    }

    //print the map
    void print_map(){
        for(int i = 0; i < len_x; i++){         //i-th row of the map
            for(int _i = 0; _i < RANGE; _i++)
                for(int j = 0; j < len_y; j++) //j-th column of the map
                    for(int _j = 0; _j < RANGE; _j++){
                        // cout << map[i][j].image[_i][_j]; 
                    }
            // cout << endl;
        }
    }

    //set a bomb
    //input: the position of the bomb
    void set_bomb(Point p){
        map[p.x][p.y].bomb = new Bomb;
        map[p.x][p.y].bomb -> set = true;
        map[p.x][p.y].bomb-> set_time = clock();
        map[p.x][p.y].empty = false;
    }
    
    
    //if the target unit is moveable
    bool if_moveable(int x, int y){     
        return map[x][y].walkable;
    }
    
    //if the target unit is breakable
    bool if_breakable(int x, int y){    
        return map[x][y].breakable;
    }
    
    //if the target unit has a prop on it
    bool if_prop(int x, int y){          
        return map[x][y].prop;          //if prop != 0, there is a prop on the map
    }
};


//Props for player to use in the game
//Porp list:
//0: heart, add one life, not in the package
//1: sheild, defend the bomb for 5 sec
//2: spring, jump over the wall once
//3: seed, for plant trees, and trees will grow coins
//4: wood, player can place a wooden wall to defend the bomb
struct Prop{

    string name;
    string description;
    int num;
    void set(string _name, string _descrip, int _num){
        name = _name;
        description = _descrip;
        num = _num;
    }
};

//Profile of the player
struct Player{
    string name;            //name of the player
    clock_t time;              //for game countdown
    bool if_protect;        //the remaining time player being protected
    Point position;         //position of the user
    int life;               //number of lives player owns
    int coins;              //number of coins that player owns
    vector<Prop> package;   //props player owns
    bool if_quit;           //if user is sure to quit the game
    Map *map;               //the chosen map

    clock_t time_protect;      //the time used

    //set the name of the player
    void set_name(string _name){
        name = _name;
    }

    //when user get a new prop
    void add_item(int num){
        if (num == 0)
            life ++;
        else package[num].num ++;
    }

    //initialize the package
    void initialize_props(){
        Prop prop; 

        prop.set("heart", "description", 0);
        package.push_back(prop);

        prop.set("shield", "description", 0);
        package.push_back(prop);

        prop.set("spring", "description", 0);
        package.push_back(prop);

        prop.set("seed", "description", 100);
        package.push_back(prop);

        prop.set("wood", "description", 100);
        package.push_back(prop);
    }

    //initilaize the player
    void initialize(){

        // setname("name");

        // time.set(0,0);
        
        if_protect = false;
        position.set(0,0);
        life = 1;
        coins = 0;
        
        initialize_props();

        if_quit = false;
    }

    //player try to move
    void move(int _x, int _y){
        if (map -> if_moveable(position.x + _x, position.y + _y)){      //if the target unit is moveable
            position.move(_x, _y);

            if (map -> if_prop(position.x, position.y)){                //if the target unit has a prop on it
                add_item(map -> map[position.x][position.y].prop);       //add the prop to the package
            }
        }
    }

    //player set a porp on the map
    //input: which prop is used
    void use_prop(int p){
        if (p == 1){            //player use a shield
            if_protect = true;
            time_protect = clock();
        }

        if (package[p].num != 0){
            // map -> set_porp(p, position.x, position.y);
            package[p].num -= 1;
        }
    }

    //player set a bomb on the map
    bool set_bomb(){
        //可能需要判断是否可放
        if (!map -> map[position.x][position.y].empty)
            return false;
        map -> set_bomb(position);
        return true;
    }

};


#endif