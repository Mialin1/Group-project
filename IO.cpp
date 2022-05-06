#include "IO.h"
#include "structure.h"


extern vector<vector<Map> > maps;

void input_maps(){

    ifstream fin;
    fin.open("maps.txt");

    if(fin.fail()){
        cout << "Error in file opening!" << endl;
        exit(1);
    }

    for(int level = 0; level < Max_Level; level ++){ //
        vector<Map> _map;
        for(int _; _ < 5; _ ++){
            Map map;
            
            fin >> map.len_x >> map.len_y;
            fin >> map.coins_need;

            map.map = new unit *[map.len_x];
            for(int i = 0; i < map.len_x; i++)
                map.map[i] = new unit [map.len_y];
        
            for(int i = 0; i < map.len_x; i++){
                for(int j = 0; j < map.len_y; j++){     //input information of unit [i, j]

                    char c; //denotes what kind of unit it is
                    fin >> c;
                    
                    if(c == 'S')
                        map.map[i][j].set("space", i, j);
                    else if (c == 'W')
                        map.map[i][j].set("wall", i, j);
                    else if (c == 'B')
                        map.map[i][j].set("box", i, j);
                }
            }

            _map.push_back(map);
        }
        maps.push_back(_map);
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
    return (char)in;
}
