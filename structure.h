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

struct Box{
    Time set_time;
    bool if_box;

    bool to_box(Time t){
        return set_time.diff(t).equal(1);///////////////////////////////////////////////to be set
    }
};

#define RANGE_X 3     //the size of each unit
#define RANGE_Y 3
//extern const int range_x = 3;

//the struct which stores the image of each unit
struct Image{
    string s[RANGE_Y];
    void set_bomb(){
        s[0] = "///";
        s[1] = "///";
        s[2] = "///";
    }
    void set_tree(){
        s[0] = "///";
        s[1] = "///";
        s[2] = "///";
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
        
        //if _ == stone
        if (_ == "stone"){
            breakable = false;
            walkable = false;
            empty = false;
        }

        //if _ == box
        if (_ == "box"){
            breakable = true;
            walkable = false;
            empty = false;
            box = new Box;
            box->if_box = true;
        }

        //if _ == space
        if (_ == "space"){
            breakable = false;
            walkable = true;
            empty = true;
        }

    }
    
};

struct Map{
    unit ** map;
    int len_x, len_y;   //the size of the map
    int coins_need;     //the number of coins needed to pass the map
    int level;
    vector<Point> empty;

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

extern vector<vector<Map>> maps;

//Props for player to use in the game
//Porp list:
//0: heart, add one life, not in the package
//1: sheild, defend the bomb for 5 sec
//2: spring, jump over the wall once
//3: seed, for plant trees, and trees will grow coins
struct Prop{
    int no;
    int num;
    void set(int _no, int _num){
        no = _no;
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
    int level;

    //about props
    Prop package[10];   //props player owns
    bool if_protect;        //the remaining time player being protected
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
    bool set_bomb();

    //player use a seed(seed--10s-->(wooden)treasure box, and when the boxes are exploded, there will be coins or props)
    bool use_seed();
};


#endif