#ifndef STRUCTURE_H
#define STRUCTURE_H

#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
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



struct Time{
    int min, sec;
    void set(int _min, int _sec){
        min = _min;
        sec = _sec;
    }
};

struct Bomb{

};

struct location{
    int x, y;
    string item;
    Player *p;
    Player *temp;
    Bomb *bptr;
    bool prop;
    bool breaked;
    bool walkable;
    bool breakable;
    bool pushable;

}; 

#define RANGE 3     //the size of each unit

//information of each unit on the map
struct unit{
    bool breakable;
    bool walkable;
    int prop;
    bool if_player;
    char image[RANGE][RANGE];
};

struct Map{
    unit ** map;
    int len_x, len_y;  //the size of the map

    void readmap(){
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

    void printmap(){
        for(int i = 0; i < len_x; i++){         //i-th row of the map
            for(int _i = 0; _i < RANGE; _i++)
                for(int j = 0; j < len_y; j++) //j-th column of the map
                    for(int _j = 0; _j < RANGE; _j++){
                        // cout << map[i][j].image[_i][_j]; 
                    }
            // cout << endl;
        }
    }


    bool if_moveable(int x, int y){
        return map[x][y].walkable;
    }
    bool if_breakable(int x, int y){
        return map[x][y].breakable;
    }
    bool if_prop(int x, int y){
        return map[x][y].prop;          //if prop != 0, there is a prop on the map
    }
};

// class World{
// public:
//     //参考原作者的写法
//     bool setted(int );//玩家是否加入游戏
//     void gameroom();//游戏大厅
//     void printroom();//输出游戏大厅
//     string mapchosen;//选择地图
//     void readmap(string);//读取地图
//     void mainmap();//主要游戏界面
//     void resetitem(int, int); //重设地图单位
//     void setitem(string, int, int, int);//设置地地图
//     string proptype();//处理道具
//     void printitem(int, int); //输出地图单位
//     void move(int, int, int, int, int, int);//玩家移动
//     void sestbomb(int );//放置水球
//     void checkbomb(int ); //检查水球状态
//     void explode(int, int, Bomb *  );//水球爆炸
//     void checkplayer();//检查玩家状态
//     void quitgame();//退出游戏
//     void outofrange(int, int);
//     void end(int);//游戏结束
//     void reset();//重新进入游戏大厅
// private:
//     // WINDOW *game, *room, *win, *quit, *mapch, *testw, *reminder;
//     location **map;
//     int ploc[4][2];
//     // Player p[4];
//     clock_t t;
//     time_t now;
//     struct tm * timeinfo;
//     int range_x, range_y;
// };


//Props for player to use in the game
//Porp list:
//0: heart, add one life
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
    Time time;              //for game countdown
    bool if_protect;        //the remaining time player being protected
    Point position;         //position of the user
    int live;               //number of lives player owns
    int coins;              //number of coins that player owns
    vector<Prop> package;   //props player owns
    bool if_quit;           //if user is sure to quit the game
    Map *map;               //the chosen map


    //set the name of the player
    void setname(string _name){
        name = _name;
    }

    //when user get a new prop
    void additem(int num){
        if (num == 0)
            live ++;
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

        time.set(0,0);
        
        if_protect = false;
        position.set(0,0);
        live = 1;
        coins = 0;
        
        initialize_props();

        if_quit = false;
    }

    //player try to move
    void move(int _x, int _y){
        if (map -> if_moveable(position.x + _x, position.y + _y)){      //if the target unit is moveable
            position.move(_x, _y);

            if (map -> if_prop(position.x, position.y)){                //if the target unit has a prop on it
                additem(map -> map[position.x][position.y].prop);       //add the prop to the package
            }
        }
    }

};


#endif