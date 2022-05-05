#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
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

    //time tick once (1 sec)
    void tick(){
        if (sec == 0)
            sec = 60, min -= 1;
        sec --;
    }

    bool equal(int _sec){
        if(min == 0 && sec == _sec)
            return true;
        return false;
    }

    //it times up
    bool if_time_up(){
        return(min == 0 && sec == 0);
    }

    //time span between two system bombs
    bool bomb_span(){
        return equal(5);
    }

    //for check the shield
    bool shield_up(){
        return equal(5);
    }
};

//Bombs
struct Bomb{
    
    Time set_time; //the time when the bomb was setted

    //functions that 
    bool effect1(Time t){
        return set_time.diff(t).equal(0);
    }

    bool effect2(Time t){
        return set_time.diff(t).equal(1);
    }

    bool explode(Time t){
        return set_time.diff(t).equal(2);
    }

    bool release(Time t){
        return set_time.diff(t).equal(5);
    }
};

struct Tree{
    Time set_time;

    bool to_tree(Time t){
        return set_time.diff(t).equal(0);
    }

    bool to_box(Time t){
        return set_time.diff(t).equal(1);
    }
};

#define RANGE_X 3     //the size of each unit
#define RANGE_Y 3

//information of each unit on the map
struct unit{
    bool breakable; //wooden_box
    bool walkable;  //props, bombs, and spaces
    bool empty;     //nothing on this unit
    Point position;
    
    Bomb *bomb;     //the bomb on this unit(if any)
    Tree *tree;
    Prop *prop;

    char image[RANGE_X][RANGE_Y];

    void set(int _, int x, int y){
        //if _ == stone
        breakable = false;
        walkable = false;
        empty = false;
        position.x = x;
        position.y = y;
        bomb = NULL;
        tree = NULL;
        prop = NULL;

        //
    }
    
};

struct Map{
    unit ** map;
    int len_x, len_y;   //the size of the map
    int coins_need;     //the number of coins needed to pass the map
    vector<unit*> empty;

    //read maps from file
    void read_map();

    //print the map
    void print_map();

    //set a bomb
    //input: the position of the bomb
    void set_bomb(Point p, Time t);

    //set a seed
    //input: the position of the seed
    void set_seed(Point p, Time t);

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
    int no_;
    int num;
    void set(string _name, string _descrip, int _num){
        name = _name;
        description = _descrip;
        num = _num;
    }
};

//Profile of the player
struct Player{

    //basic information
    string name;            //name of the player
    Time time_remain;       //for countdown
    Point position;         //position of the user
    int life;               //number of lives player owns
    int coins;              //number of coins that player owns
    bool if_quit;           //if user is sure to quit the game
    Map *map;               //the chosen map

    //about props
    Prop package[10];   //props player owns
    bool if_protect;        //the remaining time player being protected
    Time time_protect;      //the moment when the shield start to work

    //when user get a new prop
    void add_item(int num);

    //initialize the package
    void initialize_props();

    //initilaize the player
    void initialize();

    //player try to move
    void move(int _x, int _y);

    //player use a spring jump
    //output: whether the jump is succeeded
    bool jump(int _x, int _y);

    //player use a shield
    void use_shield();

    //player set a bomb on the map
    bool set_bomb();

    //player use a seed(seed--5s-->tree--10s-->(wooden)treasure box, and when the boxes are exploded, there will be coins or props)
    bool use_seed();
};


#endif