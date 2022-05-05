#include <iostream>
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
}

//functions below are page generator
//maybe use a string array to store the page to be printed

//a page with welcome information
void welcome_page(Player *player){
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
        cin >> name;
        if (isalnum(name[0])){
            player->name =name;
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
        cout<<"||    1. Your Mr. Bomber initially has one life. Watch out   ||"<<endl;//only has one life initially,...but of course, you will have chances to earn more life in the game!
        cout<<"||       for the bombs! You will lose 1 life if hurt by it.  ||"<<endl;
        cout<<"||    2. You will have to restart the same level if you      ||"<<endl;
        cout<<"||       Lose all your life / Don't meet the requirement.    ||"<<endl;//结束条件讨论
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

void room_page(Player *player){
    
    string command;
    string lines[4];

    lines[0]="Please Enter the number: ";
    lines[1]="1: Start a new game";
    lines[2]="2: Load from save";
    lines[3]="3: Exit the game";

    while(1){
        refresh();
        logo_interface();
        print_page(lines,sizeof(lines[0])+2);
        cin>>command;
        if(command=="1"||command=="2"){
            break;
        }
        else if(command=="3"){
            quit_page();
        }
        else{
            lines[0]="Invalid Input! Please Enter the number again: ";
        }
    }
    
   
    for(int i = 0; i < 10; i ++){
        //generate the loading bar by time
        refresh();
        string load[1];
        load[0]="Loading.........";
        print_page(load,sizeof(load[0]));
    }

    if (command=="1"){
        choose_level_page();
    }

    //list out all the maps for users to choose
    //higher level map may be locked, the locked map should be gray
    print_page();

    //player->map = ;
    //press ____ to choose the map and quit room_page
}

void choose_level_page(){
    string level[5];
    for(int i=0;i<20;i++){
        if()
    }
    
}
void name_bar(Player player){
    string name_bar[3];
    name_bar[0]="Player: "+player.name;
    name_bar[1]="LEVEL "+;
    print_page(name_bar,sizeof(name_bar[0]));
}

void status_bar()
void game_page(Player player){
    name_bar(player);
    
    //player: Player_Name
    //level: 1
    // -------------------------    
    //|                         |   up (W)
    //|                         |   down (S)
    //|                         |   left (A)
    //|                         |   right (D)
    //|                         |   shield (shift+1): 5
    //|                         |   spring (shift+2): 3   
    //|                         |   seed   (shift+3): -
    //|                         |   bomb   (space): -
    //|                         |
    // -------------------------
    // life: 1    coin(s): 0/100
    // time remaining:    03: 00

    //maybe also use struct func (map.print_map())
    //or turn the struct func to a generator and also use the print_page() functoin
    print_page;
    
    
}

void quit_page(){

    //See you next time
    print_page;
    quit_game;
}

void leave_page(Player *player){
    //Do you want to leave the game?
    //yes(y)            no(n)
    print_page();

    char x = get_input();
    if (x =='y') {
        player -> if_quit = true;
        //new page
        //Do you want to save your game?
        //yes(y)            no(n)

        x = get_input();
        if (x == 'y'){
            //save the status to file
            //to be saved: 
            //status: Profile and Map
        }
        //new page
        //The status is succesfully saved
    }
        

    
    
    
    

    
    
}

// bool quit_game(Player player){
//     return player.if_quit;
// }

void dead(Player player){
    //small window: Sorry, you are dead
    //press any key to continue
    player.initialize();
    room_page(&player);
}

//when time is up, check whether the coins meet the requirement
void check_page(Player player){
    
    //You need (player.map->coins_need) coins to pass this round
    //you have (player.coins) coins
    
    print_page();

    if (player.coins >= player.map -> coins_need){
        //Congratulations! .....
        //do you want to enter a bigger map?
        //yes(y)  no(n)
        print_page();

        //if yes
        room_page(&player);

        //if no
        leave_page(&player);
    }
    
}

void warning(){
    //invalid move/operation
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
    line[1]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
    line[2]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
    line[3]= "OOOO                                                                OOOO";
    line[4]= "OOOO                                                                OOOO";
    line[5]= "OOOO     ░█▀▄▀█ █▀▀█      ░█▀▀█ ░█▀▀▀█ ░█▀▄▀█ ░█▀▀█ ░█▀▀▀ ░█▀▀█     OOOO";
    line[6]= "OOOO     ░█░█░█ █▄▄▀      ░█▀▀▄ ░█──░█ ░█░█░█ ░█▀▀▄ ░█▀▀▀ ░█▄▄▀     OOOO";
    line[7]= "OOOO     ░█──░█ █─▀█ █    ░█▄▄█ ░█▄▄▄█ ░█──░█ ░█▄▄█ ░█▄▄▄ ░█─░█     OOOO";  
    line[8]= "OOOO                                                                OOOO";
    line[9]= "OOOO                                                                OOOO"; 
    line[10]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"; 
    line[11]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"; 
    line[12]= " ";

    for(int i=0; i<13; i++){
        cout<<line[i]<<endl;
    }

}


// Function: to format the string
string format_string(string str, const int & new_len)
{
	while ( str.length() < new_len )
		str += " ";
	return str.substr(0, new_len);
}

//refresh the screen
void refresh(){
    system("clear");
    cout<<endl;
}


