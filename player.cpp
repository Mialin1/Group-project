#include "structure.h"
using namespace std;

//initilaize the player for a round
void Player::initialize(){

    time_remain.set(1, 30); //3 mins per round
    position.set(0,0);
    life = 1;
    coins = 0;
    if_quit = false;
    map = NULL;

    initialize_props();

    if_protect = false;
    
}

//initialize the package
void Player::initialize_props(){
    package[0].set(0, 0);//heart
    package[1].set(1, 0);//shield
    package[2].set(2, 0);//spring
    package[3].set(3, 10);//seed
}

//when user get a new prop
void Player::add_item(Prop *p){
    if (p->no == 0) //heart
        life ++;
    else if (p->no > 3) //coins
        coins += p->num;
    else 
        package[p->no].num ++; //other props
}



//player try to move
void Player::move(int _x, int _y){
    if(position.x + _x < 0 || position.x + _x >= map->len_x
    || position.y + _y < 0 || position.y + _y >= map->len_y) //out of range
        return;
    unit &u = map -> map[position.x + _x][position.y + _y];
    if (u.walkable){         //if the target unit is moveable
        position.move(_x, _y);
        if (u.prop != NULL){ //if the target unit has a prop on it
            add_item(u.prop);     //add the prop to the package
            delete u.prop;
            u.prop = NULL;
            u.set("space", _x, _y);     //set the unit to space
        }
    }
}

//player use a spring jump
//output: whether the jump is succeeded
bool Player::jump(int _x, int _y){
    if(position.x + _x < 0 || position.x + _x >= map->len_x
    || position.y + _y < 0 || position.y + _y >= map->len_y) //out of range
        return false;

    unit &u = map -> map[position.x + _x][position.y + _y];

    if (u.walkable){         //if the target unit is moveable
        position.move(_x, _y);

        if (u.prop != NULL){         //if the target unit has a prop on it
            add_item(u.prop);     //add the prop to the package
            delete u.prop;
            u.prop = NULL;
            u.set("space", _x, _y);       //set the unit to space
        }
        package[2].num --;
        return true;
    }
    return false;
}

//player use a shield
void Player::use_shield(){
    package[1].num --;
    if_protect = true;
    time_protect = time_remain;
}

//player set a bomb on the map
void Player::set_bomb(){
    unit u = map->map[position.x][position.y];
    if (!u.empty)
        return;
    Time t;
    t.set(time_remain.min, time_remain.sec - 2);
    map -> set_bomb(position, time_remain);
}

//player use a seed(seed--10s-->(wooden)treasure box, and when the boxes are exploded, there will be coins or props)
bool Player::use_seed(){
    if (!map -> map[position.x][position.y].empty)
        return false;
    map -> set_seed(position, time_remain);
    package[3].num --;
    return true;
}