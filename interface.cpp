#include "interface.h"
#include "structure.h"
#include "IO.h"
using namespace std;

void _sleep(int s, int ns){
    struct timespec ts, ts1;
    ts.tv_nsec = ns;
    ts.tv_sec = s;
    nanosleep(&ts, &ts1);
}

//all the pages are printed by this function
void print_page(string passage[], int length, int size){
    length += 10;
    for(int i=0; i<length + 4 ;i++){
        cout<<"-";
    }
    cout<<endl;
    for(int i=0; i< size; i++){
        cout<<"| "<< format_string(passage[i],length) << " |" << endl;
    }
    for(int i=0; i<length + 4;i++){
        cout<<"-";
    }
    cout<<endl;
}

//functions below are page generator
//maybe use a string array to store the page to be printed

//a page with welcome information
void welcome_page(Player &player){
    player.if_quit = true;
    //first ask the user to input his/her name.

    string name;
    string command;
    bool valid=true;
  
    while (1){
        refresh();
        logo_interface();
        if (valid=true){
            cout<<"===============================================================" << endl;
            cout<<"||  Welcome to MR.BOMBER !                                   ||" << endl;
            cout<<"||  Please input your name(begin with letter/number):        ||" << endl;
            cout<<"===============================================================" << endl;
        }
        else{
            cout<<"===============================================================" << endl;
            cout<<"||  Welcome to MR.BOMBER !                                   ||" << endl;
            cout<<"||  Invalid input,                                           ||" << endl;
            cout<<"||  Please input your name again(begin with letter/number):  ||" << endl;
            cout<<"===============================================================" << endl;
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
        cout<<"||      wall once,you need to first press keyboard then      ||"<<endl;
        cout<<"||      press the direction you want to go.                  ||"<<endl;
        cout<<"==============================================================="<<endl;
        cout<<""<<endl;
        if (valid==true){
            cout<<"---------------------------------------------------------------"<<endl;
            cout<<"Are you ready to starts?                                      "<<endl;
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

} 

void room_page(Player &player){
    player.if_quit = true;
    string lines[4];
    lines[0]="Please ENTER the corresponding number";
    lines[1]="(0-5): Enter the level number you want to start";
    lines[2]="6: Load from save";
    lines[3]="7: Exit the game";

    string command;
    while(1){
        refresh();
        logo_interface();
        print_page(lines,sizeof(lines[1]),4);
        print_level(player.level);
        cin >> command;
        if(command.length() == 1 && command[0] >= '0' && command[0]<='7' ){
            break;
        }
        else{
            lines[0]="Invalid Input! Please Enter the number again: ";
            continue;
        }
    }
    if(command == "7"){
        leave_page(player);
        room_page(player);
    }
    else if (command == "6"){
        input_level(player);
        room_page(player);
    }
    //higher level map may be locked, the locked map should be gray
    else{
        int level = command[0] - '0';
        while(1){
            if (level <= player.level){
                break;
            }
            else{
                cout<<"The level is locked,\n please choose the blue highlighted level"<<endl;
                print_level(player.level);
                cin>>level;
            }
        }
        print_loading();
        player.initialize();

        if(level ==1) player.time_remain.set(1, 30);
        if(level ==2) player.time_remain.set(1, 45);
        if(level ==3) player.time_remain.set(2, 00);
        if(level ==4) player.time_remain.set(2, 15);
        if(level ==5) player.time_remain.set(2, 30);
        if(level ==6) player.time_remain.set(2, 45);


        int x = rand()%3;
        player.map = new Map;
        player.map->build_map(level, x);//randomly select a map
        game_page(player);
        _sleep(0, 10);

    }

        
    
}

//generate the loading bar by time
void print_loading(){
    refresh();
    string load[1];
    load[0]="Loading.........";
    print_page(load,sizeof(load[0]),1);
    _sleep(2, 0);
}



    //list out all the levels for users to choose
void print_level(int l){
    string level[3];
    string line;
    int now=1;
    level[0]=" (only can choose the blue highlighted level)";
    for(int i=0;i<6;i++){
        if (i==0||i==3){
            line="";
        }
        if(i<=l){
            line+="\033[1m\033[34mLevel "+to_string(i)+"   \033[0m";
        }
        else{
            line+="\033[2mLevel "+to_string(i)+"   \033[0m";
        }
        if(i==2||i==5){
            level[now]=line;
            now++;
        }  
    }
    for(int i=0; i<3;i++){
        cout<<level[i]<<endl;
    }
}


void print_name(Player player){
    string name_bar[2];
    name_bar[0]="Player: " + player.name + "            Press 'e' to exit";
    name_bar[1]="Your LEVEL: "+to_string(player.level) + "               Map LEVEL: " + to_string(player.map->level);
    print_page(name_bar,45,2);
}

//display props in the pocket and their instruction
void print_prop_instruction(Player player){
    string instruct[4];
    if (player.if_protect==true)
        instruct[0]="[Using] \033[34m\u25C6\033[0m Shield(press 'j'): "+to_string(player.package[1].num);
    else
    instruct[0]="\033[34m\u25C6\033[0m Shield(press 'j'): "+to_string(player.package[1].num);
    instruct[1]="\u2605 Spring(press 'k'): "+to_string(player.package[2].num);
    instruct[2]="\033[32m???\033[0mSeed(press 'l'): "+to_string(player.package[3].num);
    instruct[3]="{\u2739} Bomb(press 'b'): no limit";
    for (int i=0;i<4;i++)
        cout<<instruct[i]<<endl;
}

//display the main game page
void game_page(Player player){
    refresh();
    print_name(player);
    Map *map=player.map;
    cout << endl;
    for(int i = 0; i < map -> len_y *RANGE_Y + 3; i++)
        cout<<"\u25BA";
    cout<<endl;
    map->print_map(player.position, player.package[1].num, player.package[2].num, player.package[3].num, player.if_protect, player.life, player.coins, player.time_remain);
    for(int i = 0; i < map -> len_y *RANGE_Y + 3; i++)
        cout<<"\u25C4";
    cout << endl;
    // print_status(player);
    // cout<<" "<<endl;
    // print_prop_instruction(player);

    
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


    
}

void quit_page(){
    refresh();
    
    cout << endl;
    cout << endl;
    cout << "?????????????????? ??????????????? ???????????????  ??????  ?????? ?????????????????? ???????????????  ????????? ?????? ??????????????? ??????????????? ???????????????  ??????????????? ????????? ?????????????????? ??????????????? " << endl;
    cout << "?????????????????? ??????????????? ???????????????  ?????????????????? ?????????????????? ???????????????  ?????????????????? ???????????????  ??????    ??????     ??????   ??????  ?????????????????? ??????????????? " << endl;
    cout << "?????????????????? ??????????????? ???????????????    ??????   ??????????????????  ????????????  ??????  ?????? ??????????????? ???????????????  ??????     ??????   ????????? ??????  ?????? ??????????????? " << endl;
    cout << endl;
    cout << endl;

    
    exit(0);
}

void leave_page(Player &player){
    player.if_quit = true;
    string leave[2];
    leave[0]="Do you want to leave the game?    ";
    leave[1]="Enter 'y' if yes; Enter 'n' if no ";
    while(1){
        refresh();
        print_page(leave, leave[1].length(),2);
        
        string x;
        cin>>x;
        if (x =="y") {
            string message[4];
            message[0]="Your level record has been loaded!";
            message[1]="Please use the same player name next time ";
            message[2]=" if your want to load the previous record";
            message[3]=" use the same username next time.";
            print_page(message,message[1].length(),4);
            output_level(player);
            if(player.map!=NULL){
                player.map->delete_map();
                delete player.map;
                player.map = NULL;
            }
            quit_page();
        }
        else if(x=="n"){
            player.if_quit = false;
            return;
        }
        else{
            leave[0]="Invalid Input.";
        }       
    }
}
    
void dead(Player &player){
    player.if_quit = true;
    player.initialize();
    string dead[3];
    string c;
    dead[0]="Sorry, your mr.bomber is dead.";
    dead[1]="Cheer up! ";
    dead[2]="Enter 'r' to restart;  Enter 'e' to exit";
    while(1){
        print_page(dead,dead[2].length(),3);
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
    player.if_quit = true;
    refresh();
    string check[4];
    Map map=*player.map;

    char x = ' ';
    while(x != 'm'){
        refresh();
        check[0]="You need "+to_string(map.coins_need)+ " coins to pass this level.";
        check[1]="You have "+to_string(player.coins)+" coins.";
        check[2]="";
        check[3]="press M to continue";
        print_page(check,check[0].length(),4);
        x = get_input();
    }
        

    
    if (player.coins >= map.coins_need){
        player.level = max(player.level, max(5, map.level + 1));
        string win[3];
        string input;
        refresh();
        congratulation_interface();
        std::cout << "              Another game or quit the game?        " << endl;
        std::cout << "              another game(y)     quit(n)           " << endl;  
        while(1){
            
            cin >> input;
            if(input == "y")
                return;
            else if(input == "n"){
                leave_page(player);
                break;
            }
            else{
                refresh();
                congratulation_interface();
                cout << "           Invalid input! Please input again: " << endl;
                cout << "              another game(y)     quit(n)           " << endl;  
            }
                
        }
    }
    else{
        no_pass(player);
    }
}

       
//if coin number doesn't meet the requirement
void no_pass(Player &player){
    player.if_quit = true;
    string nopass[3];
    cout << "Sorry, your coin number doesn't meet the requirement." << endl;
    cout << "Cheer up and try again! " << endl;
    cout << endl;
    cout << "Enter 'r' to start a new game; Enter 'e' to exit" << endl;
    
    while(1){
        string input;
        cin >> input;
        if(input == "r"){
            return;
        }
        if(input == "e"){
            leave_page(player);
        }
        else{
            refresh();
            cout << "Invalid Input!" << endl;
            cout << "Enter 'r' to start a new game; Enter 'e' to exit" << endl;
        }
    }
}    

//function: output message of invalid move/operation
void warning(){
    string warning[2];
    warning[0]="invalid move/operation";
    warning[1]="Please input again!";
    print_page(warning,warning[0].length(),2);
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
    line[5]= "OOOO     ?????????????????? ????????????      ??????????????? ?????????????????? ?????????????????? ??????????????? ??????????????? ???????????????     OOOO";
    line[6]= "OOOO     ?????????????????? ????????????      ??????????????? ?????????????????? ?????????????????? ??????????????? ??????????????? ???????????????     OOOO";
    line[7]= "OOOO     ?????????????????? ???????????? ???    ??????????????? ?????????????????? ?????????????????? ??????????????? ??????????????? ???????????????     OOOO";  
    line[8]= "OOOO                                                                OOOO";
    line[9]= "OOOO                                                                OOOO"; 
    line[10]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"; 
    line[11]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"; 
    line[12]= " ";

    for(int i=0; i<13; i++){
        cout<<line[i]<<endl;
    }

}

//print our logo "MR. BOMBER" is the main interface
void congratulation_interface(void){
    string line[13];

    line[0]= " ";
    line[1]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO000000000000000000000000000000000000000";
    line[2]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO000000000000000000000000000000000000000";
    line[3]= "OOOO                                                                                                       OOOO";
    line[4]= "OOOO                                                                                                       OOOO";
    line[5]= "OOOO     ??????????????? ?????????????????? ????????? ?????? ??????????????? ??????????????? ??????????????? ??????????????? ?????? ?????? ??????    ??????????????? ??????????????? ????????? ?????????????????? ????????? ?????? ??????????????????      OOOO";
    line[6]= "OOOO     ??????    ??????  ?????? ?????????????????? ?????? ?????? ??????????????? ???????????????  ??????   ?????? ?????? ??????    ???????????????  ??????   ??????  ??????  ?????? ??????????????????  ???????????????      OOOO";
    line[7]= "OOOO     ??????????????? ?????????????????? ??????  ?????? ??????????????? ?????? ?????? ?????? ??????  ??????   ??????????????? ??????????????? ?????? ??????  ??????   ????????? ?????????????????? ??????  ?????? ??????????????????      OOOO";  
    line[8]= "OOOO                                                                                                       OOOO";
    line[9]= "OOOO                                                                                                       OOOO"; 
    line[10]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO000000000000000000000000000000000000000";
    line[11]= "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO000000000000000000000000000000000000000";
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


