#include "IO.h"
#include "structure.h"
#include <iostream>
#include <fstream>

char get_input(){
    return 'w';
}

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

            map.map = new unit *[map.len_x];
            for(int i = 0; i < map.len_x; i++)
                map.map[i] = new unit [map.len_y];
        
            for(int i = 0; i < map.len_x; i++){
                for(int j = 0; j < map.len_y; j++){
                    //input information of unit [i, j]
                    string _;  //_ denotes what kind of unit it is
                    cin >> _;
                    map.map[i][j].set(_, i, j);

                    //add the empty ones to the queue
                    if (map.map[i][j].empty){
                        unit *u = &map.map[i][j];
                        Point p;
                        p.set(i,j);
                        map.empty.push_back(p);
                    }

                }
            }

            _map.push_back(map);
        }
        maps.push_back(_map);
    }

    fin.close();
}