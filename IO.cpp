#include "IO.h"
#include "structure.h"
#include <termio.h>

void input_level(Player &player){
    ifstream fin;
    string s = player.name + ".txt";
    fin.open(s.c_str());

    if(fin.fail()){
        cout << "Error in file opening!" << endl;
        exit(1);
    }

    fin >> player.level;

    fin.close();
}

void output_level(Player player){
    ofstream fout;
    string s = player.name + ".txt";
    fout.open(s.c_str());

    fout << player.level;

    fout.close();
}

void input_maps(){

    ifstream fin;
    fin.open("map.txt");

    if(fin.fail()){
        cout << "Error in file opening!" << endl;
        exit(1);
    }

    for(int level = 0; level < Max_Level; level ++){ 
        for(int _ = 0; _ < 3; _ ++){
            int x, y, c;
            fin >> x >> y >> c;
            maps_size[level][_][0] = x;
            maps_size[level][_][1] = y;
            maps_coin[level][_] = c;

            for(int i = 0; i < x; i ++) fin >> maps[level][_][i];
        }
    }

    fin.close();
}

char get_input()
{
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);
     
    in = getchar();
     
    tcsetattr(0,TCSANOW,&stored_settings);
    char x = (char) in;
    return x;
}
