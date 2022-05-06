# Proposal

- Group No. : 211
- Group Members: Huang Leyang(3035845899), Lin Liya
- Topic: Mr. Bomb

## 1. Introduction of Game

The proposed game, "Mr. Bomb", is an adventure RPG game. The player can enjoy the excitement of surviving from bombs, making use of varieties of props, and collecting coins.  By putting bombs to blow up the wooden boxes, player may get helpful props or coins. Random bombs may fall from time to time, and if the player can survive the game and get enough gold coins within the limited time, he or she can unlock more challenging game in higher level.

## 2. Rules of the Game

### 2.1 rules for survival

The player initially has one life. If the player luckily collect a "heart" prop, he or she can add one extra life. When the bomb unfortunately explode near the user, he or she will get life deduction. If the life status becomes zero, the player dies, which also means the player has lost the game.

### 2.2 rules for passing to next level

If the player can survives from the bombs, and the coins collected has meet the requirement, he or she will pass to the next level, and will be able to have more challenging game (larger map, more frequent bombs, and higher coin collect requirement).

### 2.3 rules for game props

1) heart: add one more life
2) shield: the player will be under protection for 10 seconds
3) spring: the player is able to directly walk though the wall once
4) seed: player can set a seed on a unit, and it will turn into a box in 10 seconds
5) bomb: it will explode 3 seconds after it is set, and its impact range is 3*3,  and it will affect everything excpet the stone wall. Boxes will be opened (and there will be chances to appear props and coins), and others will be turned into dust.

### 2.4 commands from the player input

1) WSAD: move (W:up, S:down, A: left, D: right)
2) B: set a bomb
3) J: use a shield
4) K: (+WSAD) use a spring
5) L: set a seed
6) E：exit the game

### 2.5 rules for the setting

1. map： 5*10 initially, and the map will enlarge while the level goes up.
2. stone wall：solid square, unbreakable, will not be affected by the bomb
3. treasure boxes: hollow square，which can be exploded and get game props,coin, or even bomb
4. player pocket: store the props
5. life bar: shows how many lives does player has
6. time: the remain time for this level
7. coins collected: show how many coins have been collected
8. coin requirement: the required coin for this level

## 3.Game Features and Requirement

### 3.1 Dynamic User Interface

The user interface is the feature responsible for input and output, displaying the visualized game on the terminal and receiving the user input from the terminal. For user input, there will be only one region - the user input line. The status interface, main interface, text interface, and user input line are arranged in a top-down manner.

- The status interface is mainly for displaying instantaneous character-related and level-related information. It contains the level number, time, life bar, props inside the pocket.
- The main interface is mainly for displaying instantaneous game content.
- The text interface is used to display any notification, and story content.

### 3.2 Data storage and Loading

Permanent data storage is manual storage that refreshes only if the specific user command is received(if press "store" in the main interface). During this process, all the character-related data, including status, time, location, level number,  pocket, will be exported to an external file and will have permanent storage.

### 3.3 Data processing

All the content displayed on the screen is based on continuously updated data. Therefore, we can conclude that all the displayed game content is actually regarding "Data Processing". With collective data processing functions, a different game feature can be created.

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
