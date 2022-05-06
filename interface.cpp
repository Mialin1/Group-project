#include "interface.h"
#include "structure.h"
#include "IO.h"
using namespace std;

//all the pages are printed by this function
void print_page(string passage[], int length){
    for(int i=0; i<length;i++){
        cout<<"-";
    }
    cout<<endl;
    for(int i=0; i<sizeof(passage)-1;i++){
        cout<<"|  "<<format_string(passage[0],length-4)<<"|"<<endl;
    }
    for(int i=0; i<length;i++){
        cout<<"-";
    }
    cout<<endl;
}

//functions below are page generator
//maybe use a string array to store the page to be printed

//a page with welcome information
void welcome_page(Player &player){
    //first ask the user to input his/her name.

    string name;
    string command;
    bool valid=true;
  
    while (1){
        refresh();
        logo_interface();
        if (valid=true){
            cout<<"===============================================================";
            cout<<"||  Welcome to MR.BOMBER !                                   ||";
            cout<<"||  Please input your name(begin with letter/number):        ||";
            cout<<"===============================================================";
        }
        else{
            cout<<"===============================================================";
            cout<<"||  Welcome to MR.BOMBER !                                   ||";
            cout<<"||  Invalid input,                                           ||";
            cout<<"||  Please input your name again(begin with letter/number):  ||";
            cout<<"===============================================================";
        }
        getline(cin, name);
        if (isalnum(name[0])){
            player.name =name;
            valid=true;
            break;
        }
        else{
            valid=false;
        }

    }
    while(1){
        refresh();
        logo_interface();
        cout<<"==============================================================="<<endl;
        cout<<"||  Nice to meet you, "<<name;
        for(int i=0; i<39-name.length();i++){
            cout<<" ";
        }
        cout<<"||"<<endl;
        cout<<"||  Kind Reminder!                                           ||"<<endl;
        cout<<"||                                                           ||"<<endl;
        cout<<"||  Here are the rules, please read them carefully:          ||"<<endl;
        cout<<"||    1. Your Mr. Bomber initially has one life. Watch out   ||"<<endl;
        cout<<"||       for the bombs! You will lose 1 life if hurt by it.  ||"<<endl;
        cout<<"||       but of course, you will have chances to earn more   ||"<<endl;
        cout<<"||       life in the game                                    ||"<<endl;
        cout<<"||    2. You will have to restart the same level if you      ||"<<endl;
        cout<<"||       Lose all your life / Don't meet the requirement.    ||"<<endl;
        cout<<"||    3. Your main goal in passing each level is to collect  ||"<<endl;  
        cout<<"||       enough coins within a limited time. The difficulty  ||"<<endl; 
        cout<<"||       will increase with the level up.                    ||"<<endl;
        cout<<"||    4. You can use bombs to explode the white boxes, but   ||"<<endl;
        cout<<"||       they will not affect the wall. When the boxes are   ||"<<endl;
        cout<<"||       demolished, there might be some surprise.           ||"<<endl;
        cout<<"||       (props, or even coins!)                             ||"<<endl;
        cout<<"||                                                           ||"<<endl;
        cout<<"||  Wait! Don't forget how to make use of those props!       ||"<<endl;      
        cout<<"||  (Trust me. They can make your life a lot easier :P)      ||"<<endl;
        cout<<"||    1.heart: add one more life                             ||"<<endl;
        cout<<"||    2.shield: the player will be in invincible mode for 5s ||"<<endl;
        cout<<"||    3.coin: count for the final grade                      ||"<<endl;
        cout<<"||    4.spring: the player can directly walk through the     ||"<<endl;
        cout<<"||      wall once                                            ||"<<endl;
        cout<<"==============================================================="<<endl;
        cout<<""<<endl;
        if (valid==true){
            cout<<"---------------------------------------------------------------"<<endl;
            cout<<"Are ready to start!?                                      "<<endl;
            cout<<"Enter 'y' to start the game!!!                          "<<endl;
        }
        else{
            cout<<"---------------------------------------------------------------"<<endl;
            cout<<"Invalid input.                                          "<<endl;
            cout<<"Please enter 'y' to start the game! Press 'e' to exit the game."<<endl;
        }
        cin>>command;
        if(command=="y"){
            break;
        }
        else if(command=="e"){
            quit_page();
        }
        else{
            valid=false;
        }

    }

};  

void room_page(Player &player){
    
    int command;
    string lines[4];
    lines[0]="Please Enter the number you want to choose: ";
    lines[1]="(1-6): Enter the level number you want to start";
    lines[2]="7: Load from save";
    lines[3]="8: Exit the game";

    while(1){
        refresh();
        logo_interface();
        print_page(lines,sizeof(lines[1])+2);
        print_level(player.level);
        cin>>command;
        if(command>=1 and command<=8){
            break;
        }
        else{
            lines[0]="Invalid Input! Please Enter the number again: ";
        }
    }
    if(command==8){
        leave_page(player);
        room_page(player);
    }

    else if (command==7){

        ////////load from file//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        room_page(player);
    }

    //higher level map may be locked, the locked map should be gray
    else{
        while(1){
            if (command<=player.level){
                break;
            }
            else{
                cout<<"The level is locked,\n please choose the blue highlighted level"<<endl;
                print_level(player.level);
                cin>>command;
            }
        }
        print_loading();
        player.initialize();
        player.map=maps[command][rand()%5];//randomly select a map////////////
        game_page(player);
    }

        
    
}

//generate the loading bar by time
void print_loading(){
    refresh();
    string load[1];
    load[0]="Loading.........";
    print_page(load,sizeof(load[0]));
    struct timespec ts, ts1;
    ts.tv_nsec = 0;
    ts.tv_sec = 2;
    nanosleep(&ts, &ts1);
    refresh();
}



    //list out all the levels for users to choose
void print_level(int l){
    string level[3];
    string line;
    int now=1;
    level[0]=" (only can choose the blue highlighted level)";
    for(int i=1;i<7;i++){
        if (i==1||i==4){
            line="";
        }
        if(i<=l){
            line+="\033[1m\033[34mLevel "+to_string(i)+"   \033[0m";
        }
        else{
            line+="\033[2mLevel "+to_string(i)+"   \033[0m";
        }
        if(i==3||i==6){
            level[now]=line;
            now++;
        }  
    }
    print_page(level,sizeof(level[1]));
}


void print_name(Player player){
    string name_bar[3];
    name_bar[0]="Player: "+player.name;
    name_bar[1]="LEVEL "+player.level;
    print_page(name_bar,sizeof(name_bar[0]));
}

void print_status(Player player){
    string status_bar[2];
    status_bar[0]="\033[1mLife  \033[31m\u2764"+to_string(player.life)+"\033[0m"+"\033[1mCoin(s)   \033[33m\u2726"+to_string(player.coins)+"\033[0m";
    status_bar[1]="time remaining:   "+to_string(player.time_remain.min)+" : "+to_string(player.time_remain.sec);
    print_page(status_bar,sizeof(status_bar[0]));
}

//display props in the pocket and their instruction
void print_prop_instruction(Player player){
    string instruct[4];
    instruct[0]="\033[34m\u25C6\033[0m Shield(press 'j'): "+to_string(player.package[1].num);
    instruct[1]="\u2605 Spring(press 'k'): "+to_string(player.package[2].num);
    instruct[2]="\033[32m。。。\033[0m Seed(press 'l'): "+to_string(player.package[3].num);
    instruct[3]="{\u2739} Bomb(press 'b'): infinite";
    print_page(instruct,sizeof(instruct[0])+3);
}

//display the main game page
void game_page(Player player){
    refresh();
    print_name(player);
    Map *map=player.map;
    cout<<" "<<endl;
    for(int i=0; i<map->len_y+4;i++){
        cout<<"\u25BA";
    }
    cout<<endl;
    map->print_map(player.position);
    for(int i=0; i<=map->len_y+4;i++){
        cout<<"\u25C4";
    }
    cout<<endl;
    cout<<" "<<endl;
    print_status(player);
    cout<<" "<<endl;
    print_prop_instruction(player);

    
    //player: Player_Name
    //level: 1
    // -------------------------    
    //|                         |   up (W)
    //|                         |   down (S)
    //|                         |   left (A)
    //|                         |   right (D)
    //|                         |   shield (): 5
    //|                         |   spring (): 3   
    //|                         |   seed   (): -
    //|                         |   bomb   (): -
    //|                         |
    // -------------------------
    // life: 1    coin(s): 0/100
    // time remaining:    03: 00

    //maybe also use struct func (map.print_map())
    //or turn the struct func to a generator and also use the print_page() functoin
   

    
    
}

void quit_page(){
    refresh();
    string quit[3];
    quit[0]="░█▀▀▀█ ░█▀▀▀ ░█▀▀▀  ░█──░█ ░█▀▀▀█ ░█─░█  ░█▄ ░█ ░█▀▀▀ ▀▄░▄▀ ▀▀█▀▀  ▀▀█▀▀ ▀█▀ ░█▀▄▀█ ░█▀▀▀ ";
    quit[1]="─▀▀▀▄▄ ░█▀▀▀ ░█▀▀▀  ░█▄▄▄█ ░█──░█ ░█─░█  ░█░█░█ ░█▀▀▀  ░█    ░█     ░█   ░█  ░█░█░█ ░█▀▀▀ ";
    quit[2]="░█▄▄▄█ ░█▄▄▄ ░█▄▄▄    ░█   ░█▄▄▄█  ▀▄▄▀  ░█  ▀█ ░█▄▄▄ ▄▀░▀▄  ░█     ░█   ▄█▄ ░█  ░█ ░█▄▄▄ ";
    
    print_page(quit,sizeof(quit[0]));

    //quit and 存状态
}

void leave_page(Player &player){
    ///////////////////////////////////////////////////////////////map.delete_map()
    string leave[2];
    leave[0]="Do you want to leave the game?    ";
    leave[1]="Enter 'y' if yes; Enter 'n' if no ";
    while(1){
        refresh();
        print_page(leave,sizeof(leave[1]));
        
        string x;
        cin>>x;
        if (x =="y") {
            player.if_quit = true;
            break;
        }
        else if(x=="n"){
            break;
        }
        else{
            leave[0]="Invalid Input.";
        }       
    }
    if (player.if_quit){
        quit_page();
    }

}
        
//if coin number doesn't meet the requirement
void no_pass(Player &player){
    player.initialize();
    refresh();
    string c;
    string nopass[3];
    nopass[0]="Sorry, your coin number doesn't meet the requirement.";
    nopass[1]="Cheer up! ";
    nopass[2]="Enter 'r' to choose level and restart; Enter'e' to exit";
    while(1){
        print_page(nopass,sizeof(nopass[0]));
        cin>>c;
        if(c=="r"||c=="e"){
            break;
        }
        else{
            nopass[1]="Invalid Input!";
        }
    }
    if(c=="r"){
        room_page(player);
    }
    else{
        leave_page(player);
    }
}    
    
    

void dead(Player &player){
    player.initialize();
    string dead[3];
    string c;
    dead[0]="Sorry, your mr.bomb is dead.";
    dead[1]="Don't despair! You can do it next time!";
    dead[2]="Enter 'r' to restart;  Enter 'e' to exit";
    while(1){
        print_page(dead,sizeof(dead[2]));
        cin>>c;
        if(c=="r"||c=="e"){
            break;
        }
        else{
            dead[1]="Invalid Input!";
        }
    }
    if(c=="e"){
        leave_page(player);
    }
    
}

//when time is up, check whether the coins meet the requirement
void check_page(Player &player){
    string check[2];
    Map *map=player.map;
    check[0]="You need "+to_string(map->coins_need)+ " coins to pass this level.";
    check[1]="You have "+to_string(player.coins)+" coins.";
    print_page(check,sizeof(check[0]));

    struct timespec ts, ts1;
    ts.tv_nsec = 0;
    ts.tv_sec = 3;
    nanosleep(&ts, &ts1);

    refresh();
    if (player.coins >= map->coins_need){
        player.level += 1;
        string win[3];
        string input;
        string input;
        win[0]="Congratulations! "+player.name;
        win[1]="Another game? ";
        win[2]="\033[1myes(y)     no(n)\033[0m";  
        while(1){
            refresh();
            print_page(win,sizeof(win[0]));
            cin>>input;
            if(input=="y"||input=="n"){
                break;
            }
            else
                win[0]="Invalid input! Please input again: ";
        }
        if(input=="y")
            room_page(player);
        else
            leave_page(player);
    }
    else{
        no_pass(player);
    }
    
}

//function: output message of invalid move/operation
void warning(){
    string warning[2];
    warning[0]="invalid move/operation";
    warning[1]="Please input again!";
    print_page(warning,sizeof(warning[0]));
}



// Function: to format the string into our expected length
string format_string(string str, const int & new_len)
{
	while ( str.length() < new_len )
		str += " ";
	return str.substr(0, new_len);
}



//print our logo "MR. BOMBER" is the main interface
void logo_interface(void){
    string line[13];

    line[0]= " ";
    line[1]= "            OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
    line[2]= "            OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
    line[3]= "            OOOO                                                                OOOO";
    line[4]= "            OOOO                                                                OOOO";
    line[5]= "            OOOO     ░█▀▄▀█ █▀▀█      ░█▀▀█ ░█▀▀▀█ ░█▀▄▀█ ░█▀▀█ ░█▀▀▀ ░█▀▀█     OOOO";
    line[6]= "            OOOO     ░█░█░█ █▄▄▀      ░█▀▀▄ ░█──░█ ░█░█░█ ░█▀▀▄ ░█▀▀▀ ░█▄▄▀     OOOO";
    line[7]= "            OOOO     ░█──░█ █─▀█ █    ░█▄▄█ ░█▄▄▄█ ░█──░█ ░█▄▄█ ░█▄▄▄ ░█─░█     OOOO";  
    line[8]= "            OOOO                                                                OOOO";
    line[9]= "            OOOO                                                                OOOO"; 
    line[10]= "            OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"; 
    line[11]= "            OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"; 
    line[12]= " ";

    for(int i=0; i<13; i++){
        cout<<line[i]<<endl;
    }

}

//refresh the screen
void refresh(){
    system("clear");
    cout<<endl;
}


