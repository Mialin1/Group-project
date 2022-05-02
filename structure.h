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

struct unit{
    bool breakable;
    bool walkable;
    int prop;
    bool if_player;
};

struct Map{
    unit ** map;
    bool if_walkable(int x, int y){
        return map[x][y].walkable;
    }
    bool if_breakable(int x, int y){
        return map[x][y].breakable;
    }
    bool if_prop(int x, int y){
        return map[x][y].prop; //if prop != 0, there is a prop on the map
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

    string name;
    Time time;
    bool if_protect;        //the remaining time player being protected
    Point position;         //position of the user
    int live;               //number of lives player owns
    int coins;              //number of coins that player owns
    vector<Prop> props;     //props player owns
    bool if_quit;
    Map *map;               //the chosen map


    //set the name of the player
    void setname(string _name){
        name = _name;
    }

    //when user get a new prop
    void additem(int num){
        if (num == 0)
            live ++;
        else props[num].num ++;
    }

    //initialize the package
    void initialize_props(){
        Prop heart;
        heart.set("heart", "description", 0);
        Prop spring;
        heart.set("spring", "description", 0);
        Prop bomb;//用户炸弹无限多个,或给个100个？
        bomb.set("bomb", "description", 100);
        Prop seed;//这个应该也是要给很多个吧，不然很难达到硬币可持续增加
        seed.set("seed", "description", 100);
        Prop shield;
        shield.set("shield", "description", 0);
        //rocket我们没办法衡量速度，因为移动是靠按键盘的，所以玩家按一下就前进一步，比较顺畅一点，对因为一般有速度的是cs那种靠鼠标移动前进的i guess
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

    //when player want to move
    void move(int _x, int _y){
        if (map -> walkable(x + _x, y + _y)){

        }
            

    }

};

struct Map{
    int len_x, len_y;

};


#endif