#include "structure.h"
#include "interface.h"
#include "update.h"
#include "IO.h"

using namespace std;

string maps[10][5][13];
int maps_size[10][5][2];
int maps_coin[10][5];

int main(){

    Player player;

    input_maps();

    player.initialize();
    player.level = 0;
    
    welcome_page(player); 
    
    //for player to choose room
    room_page(player);

    //one more thread to update the screen per_sec no matter the player moves or not
    thread update (map_update, ref(player));
    update.detach();

    
    while(1){       //refresh the interface when get a command or time refresh

        if (player.if_quit){
            quit_page();
            break;
        }
        else {
            char x = get_input();

            switch(x){
                case 'w': //move upward
                {
                    player.move(-1, 0);
                }
                case 's': //move downward
                {
                    player.move(1, 0);
                }
                case 'a': //move leftward
                {
                    player.move(0, -1);
                }
                case 'd': //move rightward
                {
                    player.move(0, 1);
                }
                case 'j': //uses shield
                {
                    if (player.package[1].num == 0)
                        continue;
                    else player.use_shield();
                }
                case 'k': //uses spring
                {
                    if (player.package[2].num == 0){
                        continue;
                    }
                    else{
                        int __ = get_input();   //the direction he face
                        int _x, _y = 0;
                        if (__ == 'w')  _x = -2, _y = 0;
                        if (__ == 's')  _x = 2,  _y = 0;
                        if (__ == 'a')  _x = 0, _y = -2;
                        if (__ == 'd')  _x = 0,  _y = 2;
                        if (!player.jump(_x, _y))
                            continue;
                    }
                }
                case 'l': //uses seed
                {
                    if(player.package[3].num == 0)
                        continue;
                    else player.use_seed();
                }
                    
                case 'b': //user set bomb
                {
                    player.set_bomb();
                    cout << "here" << endl;
                }
                case 'e': //quit gamef
                {
                    cout << "here" << endl;
                    leave_page(player);
                }
                    
            }
            game_page(player);
        }
        
    }
}
