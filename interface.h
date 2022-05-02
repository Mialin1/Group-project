#ifndef INTERFACE_H
#define INTERFACE_H

#include "structure.h"


void welcome_page(Profile *player);

void game_page();

void quit_page();

void room_page(Profile *player);

bool quit_game(Profile player);


#endif