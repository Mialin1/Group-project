#include "player.h"
using namespace std;

//when user get a new prop
void Player::add_item(int num){
    if (num == 0)
        life ++;
    else package[num].num ++;
}

//initialize the package
void Player::initialize_props(){
    Prop prop; 

    prop.set("heart", "description", 0);
    package.push_back(prop);

    prop.set("shield", "description", 0);
    package.push_back(prop);

    prop.set("spring", "description", 0);
    package.push_back(prop);

    prop.set("seed", "description", 20);  //not too much, but have a few
    package.push_back(prop);

    prop.set("wooden wall", "description", 100); //infinite num of wooden wall
    package.push_back(prop);
}

//initilaize the player
void Player::initialize(){
    //how to initial time?? to be decided
    if_protect = false;
    position.set(0,0);
    life = 1;
    coins = 0;
        
    initialize_props();

    if_quit = false;
}

//player try to move
void Player::move(int _x, int _y){
    if (map -> map[position.x + _x][position.y + _y].walkable){      //if the target unit is moveable
        position.move(_x, _y);

        if (map -> map[position.x + _x][position.y + _y].prop){                //if the target unit has a prop on it
            add_item(map -> map[position.x][position.y].prop);       //add the prop to the package
        }
    }
}

//player use a spring jump
//output: whether the jump is succeeded
bool Player::jump(int _x, int _y){
    if (package[2].num == 0)   //has no spring
        return false;
    if (map -> map[position.x + _x][position.y + _y].walkable){      //if the target unit is moveable
        position.move(_x, _y);

        if (map -> map[position.x + _x][position.y + _y].prop){                //if the target unit has a prop on it
            add_item(map -> map[position.x][position.y].prop);       //add the prop to the package
        }
        return true;
    }
    return false;
}

//player use a shield
void Player::use_shield(){
        if_protect = true;
        time_protect = time_remain;
}

//player set a bomb on the map
bool Player::set_bomb(){
    if (!map -> map[position.x][position.y].empty)
        return false;
    map -> set_bomb(position, time_remain);
    return true;
}

//player use a seed(seed--5s-->tree--10s-->(wooden)treasure box, and when the boxes are exploded, there will be coins or props)
bool Player::use_seed(){
    if (package[3].num == 0 )
        return false;
    if (map -> map[position.x][position.y].empty){
        map -> set_seed(position, time_remain);
        return true;
    }
    return false;
}