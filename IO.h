#ifndef IO_H
#define IO_H

#include "structure.h"

extern vector<vector<Map> > maps;

void input_level(Player &player);
void output_level(Player player);
char get_input();
void input_maps();

#endif