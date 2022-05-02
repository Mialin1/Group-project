/*
 * @Author: HuangLeyang
 * @since: 2022-04-30 11:42:31
 * @lastTime: 2022-04-30 13:18:22
 * @message: This author is asomething blablablabla

 */
#include "structure.h"
#include "interface.h"
#include<cstdio>
#include<iostream>
#include<chrono>
using namespace std;

int main(){

    Profile player;

    player.initialize();
    
    welcome_page(&player); 
    
    //press space/enter to enter the game map
    while(1){
        
    }
++
