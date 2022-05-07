#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <thread>
using namespace std;

#define Max_Level 6

extern string maps[10][5][13];
extern int maps_size[10][5][2];
extern int maps_coin[10][5];

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
    bool bomb_span(int level){
        return (min == 0 && sec == 10 - level); 
    }

    //for check the shield
    bool shield_up(){
        return equal(10);
    }
};

//Bombs
struct Bomb{
    
    Time set_time; //the time when the bomb was setted

    //functions that 
    bool effect1(Time t){
        return set_time.diff(t).equal(1);
    }

    bool effect2(Time t){
        return set_time.diff(t).equal(2);
    }

    bool explode(Time t){
        return set_time.diff(t).equal(3);
    }

    bool release(Time t){
        return set_time.diff(t).equal(5);
    }
};

struct Box{
    Time set_time;
    bool if_box;

    bool to_box(Time t){
        return set_time.diff(t).equal(10);
    }
};

#define RANGE_X 3     //the size of each unit
#define RANGE_Y 4
//extern const int range_x = 3;

//the struct which stores the image of each unit
struct Image{
    string s[RANGE_X];
    void set_bomb(){
        s[0] = "  - ";
        s[1] = " {\u2739}";
        s[2] = "  - ";
    }
    void set_seed(){
        s[0] = "\033[32m。。\033[0m";
        s[1] = "\033[32m。。\033[0m";
        s[2] = "\033[32m。。\033[0m";
    }
    void set_box(){
        s[0]=" \033[33m===\033[0m";
        s[1]=" \033[33m===\033[0m";
        s[2]=" \033[33m===\033[0m";
    }
    void set_heart(){
        s[0]="  \033[31m- \033[0m";
        s[1]="  \033[31m\u2764\033[0m ";
        s[2]="  \033[31m- \033[0m";
    }
    void set_shield(){
        s[0]=" \033[34m---\033[0m";
        s[1]=" \033[34m|\u25C6|\033[0m";
        s[2]=" \033[34m---\033[0m";
    }
    void set_wall(){
        s[0]=" ===";
        s[1]=" = =";
        s[2]=" ===";
    }
    void set_spring(){
        s[0]=" ~~~";
        s[1]="  \u2605 ";
        s[2]=" ~~~";
    }
    void set_space(){
        s[0]="    ";
        s[1]="    ";
        s[2]="    ";
    }
    void set_coin(){
        s[0]="    ";
        s[1]=" \033[33m\u2666\u00A9\u2666\033[0m";
        s[2]="    ";
    }
    void seed_used(){
        s[0]=" \033[32m ^ \033[0m";
        s[1]=" \033[32m/_\\\033[0m";
        s[2]=" \033[32m ≡ \033[0m"; 
    }
};

//Props for player to use in the game
//Porp list:
//0: heart, add one life, not in the package
//1: sheild, defend the bomb for 5 sec
//2: spring, jump over the wall once
//3: seed, growing up and become a box
struct Prop{
    int no;
    int num;
    void set(int _no, int _num){
        no = _no;
        num = _num;
    }
};

//information of each unit on the map
struct unit{
    bool breakable; //wooden_box
    bool walkable;  //props, bombs, and spaces
    bool empty;     //nothing on this unit
    
    Bomb *bomb;     //the bomb on this unit(if any)
    Box *box;       //the treasure box on this unit(if any)
    Prop *prop;     //the prop on this unit(if any)

    Image image; 

    //for map generation
    void set(string _, int x, int y){
        bomb = NULL;
        box = NULL;
        prop = NULL;
        
        if (_ == "wall"){
            breakable = false;
            walkable = false;
            empty = false;
            image.set_wall();
        }

        if (_ == "box"){
            breakable = true;
            walkable = false;
            empty = false;
            box = new Box;
            box->if_box = true;
            image.set_box();
        }

        if (_ == "space"){
            breakable = false;
            walkable = true;
            empty = true;
            image.set_space();
        }

        if (_ == "prop"){
            breakable = true;
            walkable = true;
            empty = false;
            
        }

        if (_ == "bomb"){
            breakable = false;
            walkable = false;
            empty = false;
            image.set_bomb();
        }

    }
    
};

struct Map{
    unit ** map;
    int len_x, len_y;   //the size of the map
    int coins_need;     //the number of coins needed to pass the map
    int level;

    //print the map
    void print_map(Point position);

    void build_map(int _level, int _);

    void delete_map();

    //set a bomb
    //input: the position of the bomb
    void set_bomb(Point p, Time t);

    //set a seed
    //input: the position of the seed
    void set_seed(Point p, Time t);

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
    int level;

    //about props
    Prop package[10];   //props player owns
    bool if_protect;        
    Time time_protect;      //the moment when the shield start to work

    //when user get a new prop
    void add_item(Prop*p);

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
    void set_bomb();

    //player use a seed(seed--10s-->(wooden)treasure box, and when the boxes are exploded, there will be coins or props)
    bool use_seed();
};


#endif