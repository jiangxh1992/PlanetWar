## Readme — “Asteroid War”

### How to compile and execute the project?
Open the xcode project file from ***"PlanetWar/proj_ios_mac/PlanetWar.xcodeproj"*** and run the project directly under iOS device or simulator. iPhone devide is strongly adviced for best game experience. The game can run on iphone devices fluently with stable **60 frames/sec**, but it can not be garanteed running on simulators or other situations.
![这里写图片描述](http://img.blog.csdn.net/20161205190318701)

![这里写图片描述](http://img.blog.csdn.net/20161205190335185)

![这里写图片描述](http://img.blog.csdn.net/20161205191026419)

### How to play this game?
#### Objective of the game

The objective is to gain weights and eliminate enemies. The balls' movement will be slower as their weight and radius growing. To be powerful enough, player is supposed to eat smaller ones as many as possible to gain weights. Player wins the game when the weight overcome the best history record. 

To add the challenge of the game, we set two game modes – time limited and time unlimited. In the mode of time limited: the player must reach the target weight in the prescribed time to earn the best record(player can gain bunus time by killing demons), otherwise he/she will lose this game. Meanwhile player should avoid being eaten by bigger ones by using specific skills, otherwise he/she dies and the game is over; In unlimited mode:weight does'nt matter, the player are supposed to kill more demons and eat more balls to get better scores, but the player may be easily be eaten by other balls if the player is too small and game will be over.

#### Menu interface
After booting this app, we first enter the game menu interface. We are supposed to input the username and select the game mode and level. Here are two games modes – time limited and time unlimited. By default, as the green hand, we go into the first level. Only when we pass some level can we be allowed to go into the following game level. Finally, we click the “Start” button to enter the game playing scene. Also, here is a button called “History” on the bottom of the interface, which is used to view the historical game-playing records(the level design is not implemented yet due to time limited).

#### Game playing scene
In the game playing scene, the hero asteroid on the center of the scene is controlled by us. It moves according to the direction of swiping screen(or tip a destination position, tip the player to stop the player's movement). Its moving speed is decided by its weight and size. The more its weight is, the slower its moving pace is. The hero can eat the tiny static particles and eat smaller asteroids(AIball) around it to gain more weight and meanwhile must avoid being encroached by the bigger ones. When playing, the hero can use two necessary skills – shooting and accelerating when the player triggers the skill button. “Shooting” is especially used to attack the demon asteroids. “Accelerating” is used to speed up itself for a while.Besides, the player's weight will lose quikly if it's touched by any demon so the player should try to kill all the demon by shooting. 

#### Game Over
In time unlimited mode, once the hero is encroached by enemy asteroids around, we lose the game, and the score is calculated according to the eaten balls number and killed demon number;

If choosing time limited mode, our aim is to maintain a as big weight as possible when time is over to overcome the best history record to be the best player.
