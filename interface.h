#ifndef INTERFACE_H
#define INTERFACE_H

#include "structure.h"
#define STEP 1


void welcome_page(Player *player);

void game_page(Player player);

void quit_page();

void room_page(Player *player);

bool quit_game(Player player);

void leave_page(Player *player);

void check_page(Player player);

void logo_interface();
void dead(Player player);

string format_string(string str, const int & new_len);

void warning();

void refresh();

#endif