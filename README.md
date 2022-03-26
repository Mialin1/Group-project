# Proposal

Group No. : 211
Group Members: Huang Leyang, Lin Liya
Topic: Mr. Bomb


## 1. Introduction of Game
The proposed game, "Mr. Bomb", is an adventure RPG game. The player can enjoy the excitement of surviving from bombs, making use of varieties of props, and collecting coins. By putting bombs to open the wooden boxes, the outcome can be helpful props, coins, or even bombs. If the player can get enough gold coins within the limited time or before death, it will get more challenging with every level, and the random bomb will occur at a higher frequency.



## 2. Rules of the Game

### 2.1 rules for surviving
The player initially has one life. If the player can collect a "heart" prop, the player can add one more life. If the bomb hits the user, he will lose one life, and if the life status becomes zero, the user dies. After death, the game will calculate the total coin collected in this level, and if it meets the requirement for passing this level, the player can go to the next level.

### 2.2 rules for passing to next level
When the user survives from the bombs after a limited time, the game will compare the coin collected by the player with the requirement. If the number is above the condition, it will pass to the next level.

### 2.3 rules for game props
1) heart: add one more life
2) shield: the player will be in invincible mode for 5 seconds
3) coin: count for the final grade
4) rocket: increase the speed of the player within the next 20 seconds
5) spring: the player is able to directly walk though the wall within the next 20 seconds
6) wood: the player can build a disposable wall which can protect itself from the bomb
7) bomb: 
  1. Placed by the user: the bomb's lethality is the nine boxes around it, but it can only explode the wooden boxes not the wall. There will be random coin, props or even bombs come out after explode the wooden boxes.
  2. the automated bomb: the bomb's lethality is the nine boxes around it. It will only hurt the uer but will not explode any other boxes.
8) seed: can be used to plant a tree

### 2.4 rules for the player
1) move: using the keyboard (W:up, S:down, A: left, D: right)
2) put the bomb: press the space key
3) press shift + (number) to use the prop in the according pocket number

### 2.5 rules for the setting
1）map： 32x32 initially, and the map will enlarge with the level-up. 
2）stone wall：solid square, which cannot be exploded
3）wooden boxes: hollow square， which can be exploded and get game props,coin, or even bomb
4) trees: they will automatically create coins, and can be exploded by bombs
5) pocket: used to store the game props
6) life bar: shows how many lives does the player has
7) time: the limited time for this level
8) coin requirement: the required coin for this level
9) level number


## 3.Game Features and Requirement

### 3.1 Dynamic User Interface
### 3.2 Data storage and Loading
### 3.3 Data processing

## 4. Code Requirement Implementation

### 4.1 Generation of random game sets or events
1) The world map is randomly generated
2) The game props generated from the wooden boxes are random
3) The location of automated bombs are random

### 4.2 Data structures for storing game status
1) Time: stores the time of the game, and is used to generate the bombs
2) Point: stores the coordinate(x and y) of the items and the player.
3) Status: recording the game status
4) Prop: stores the information and the usage of the game props
5) Bagpack/Profile: stores the player information(what props player has, life status, coin numbers, etc.)
6) Bomb: holds the location of the bomb and the time for it to bomb

### 4.3 Dynamic memory management
For the list of bombs, the dynamic feature allows it to extend only when necessary. This could be achieved by copying the old one to the new large list, delete the old list and point the pointer to the new list. 

### 4.4 File input and output
1) file input: reading the data of structure Profile(contains life, status, and other information) from external file "profile.txt". 
2) file output: store the user information into "profile.txt"


### 4.5 Program codes in multiple files
Files: "makefile", "main.cpp", "game_status.h", "game_status.cpp”, “map.cpp” “map.h”etc.

Coding in multiple files helps us to better divide the work by parts, and help us to better cooperate with each others.

