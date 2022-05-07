# Proposal

- Group No. : 211
- Group Members: Huang Leyang(3035845899), Lin Liya(3035952018)
- Topic: Mr. Bomber

## 1. Introduction of Game

The proposed game, "Mr. Bomb", is an adventure RPG game, inspired by the game Crazy-Arcade, which is one of the best and enjoyable game in our childhood. The player can enjoy the excitement of surviving from bombs, making use of varieties of props, and collecting coins.  By putting bombs to blow up the wooden boxes, player may get helpful props or coins. Random bombs may fall from time to time, and if the player can survive the game and get enough gold coins within the limited time, he or she can unlock more challenging game in higher level.

## 2. Rules of the Game

### 2.0 command to run the code (dark mode recommended)

make game

### 2.1 rules for survival

The player initially has one life. If the player luckily collect a "heart" prop, he or she can add one extra life. When the bomb unfortunately explode near the user, he or she will get life deduction. If the life status becomes zero, the player dies, which also means the player has lost the game.

### 2.2 rules for passing to next level

If the player can survives from the bombs, and the coins collected has meet the requirement, he or she will pass to the next level, and will be able to have more challenging game (larger map, more frequent bombs, and higher coin collect requirement).

### 2.3 rules for game props

1) heart: add one more life
2) shield: the player will be under protection for 10 seconds
3) spring: the player is able to directly walk though the wall once
4) seed: player can set a seed on a unit, and it will turn into a box in 10 seconds
5) bomb: it will explode 3 seconds after it is set, and its impact range is 3*3,  and it will affect everything except the stone wall. Boxes will be opened (and there will be chances to appear props and coins), and others will be turned into dust.

### 2.4 commands from the player input

1) WSAD: move (W:up, S:down, A: left, D: right)
2) B: set a bomb
3) J: use a shield
4) K: (+WSAD) use a spring
5) L: set a seed
6) E：exit the game

### 2.5 rules for the setting

1. map： 5*10 initially, and the map will enlarge while the level goes up.
2. stone wall：white hollow square, unbreakable, will not be affected by the bomb
3. treasure boxes: yellow square，which can be exploded and get game props,coin, or even bomb
4. player pocket: store the props
5. life value: shows how many lives does player has
6. The countdown watch: the remain time for this level
7. coins collected: show how many coins have been collected
8. coin requirement: the required coin for this level

## 3.Game Features and Requirement

### 3.1 Dynamic User Interface

Our game is able to capture the real-time keyboard event and use it to form a colorful terminal user interface, displaying the constantly refreshing game effect on the terminal, providing a better gaming experience . Apart from the welcome information and instructions, the game page is mainly composed of three parts: map view, status bar, and prop instructions

- The status bar is mainly for displaying instantaneous character-related and level-related information, including player level, map level, remaining time, life bar, collected coins number, and so on.
- The map view is mainly for displaying instantaneous game content, including the map components, bombs exploding effect, and the player's' moving path.
- The prop instructions are for displaying the instantaneous prop number and the key to use it

### 3.2 Data storage and Loading

Permanent data storage is automaticly done everytime player quit the game to save the highest level the player has reached, and if he/she can choose to load his/her game status next time when he/she enter the game as long as he/she use the same username( choose "load from save" option in the map choosing page). During this process, the player information will be exported to an external file (named by the player's username)and will have permanent storage.

### 3.3 Data processing

All the content displayed on the screen is based on continuously updated data, so it can be concluded that all the displayed game content is actually regarding "Data Processing". With collective data processing functions, a different game feature can be created.

### 3.4 Multi-thread process

System activity and user input activity are processed in two different threads, while keyboard event responses (player move, player set bombs, and player use props)are done in the main threads, system update are done in the second thread every seconds()

## 4. Code Requirement Implementation

### 4.1 Generation of random game sets or events

1) The world map is randomly selected from the map library
2) The game props or coins generated from the wooden boxes are random events
3) The location of system bombs are randomly choosed

### 4.2 Data structures for storing game status

1) Time: a struct with two integers and few functionsus for game countdown , prop effect, and system bombs generation.
2) Point: stores the coordinate(x and y) of the items and the player.
3) Prop: stores the information and the number of the game props
4) Profile: stores the player information(what props player has, life status, coin numbers,.)
5) Bomb: holds the location of the bomb and the setted time(for effect generation)
6) Box: holds the set time(it may be turned from a seed)
7) Map: has level, and sores the 2d information
8) Unit: a unit on the map, has member to stores the properties(if breakable, walkable, or empty for placing a prop/bomb), and the pointer to the bomb/box/prop on it.
9) Image: stores the image information of a unit

### 4.3 Dynamic memory management

1. Bomb: every bomb(both by system and user) is generated using dynamic memory. Deleted after explosion.
2. Prop: it is dynamically generated while the box being blown up, and was deleted when picked by user or exploded by the bomb
3. Box: dynamically generated when the seed was set on the map by user or when setted in the initial map from the library, deleted when blown up.

### 4.4 File input and output

1) file input:
   1) input map libraries from file
   2) load previous game from file
2) file output:
   1) output the user information into "username.txt"

### 4.5 Seperate complilation

Files: "Makefile", "main.cpp","structure.h",  "interface.cpp", "interface.h" "IO.cpp”, "IO.h", “map.cpp” “player.cpp”etc.

Coding in multiple files helps us to better divide the work by parts, and help us to better cooperate with each others.
