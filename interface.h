#ifndef INTERFACE_H
#define INTERFACE_H
#include "structure.h"
#include "IO.h"
using namespace std;
#define STEP 1

void print_page(string passage[], int length, int size);

void welcome_page(Player &player);

void game_page(Player player);

void quit_page();

void print_loading();

void room_page(Player &player);

void print_level(int l);

bool quit_game(Player player);

void leave_page(Player &player);

void check_page(Player &player);

void logo_interface();

void print_name(Player player);

void print_status(Player player);

void print_prop_instruction(Player player);

void dead(Player &player);

string format_string(string str, const int & new_len);

void no_pass(Player &player);

void warning();

void refresh();

#endif