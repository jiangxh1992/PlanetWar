# ASTEROID WAR Documentation

This is the documentation of ios game ASTEROID WAR. The game is designed by Group T as the group assignment of COMP7506 Smart phone apps development, a course of Hong Kong University in 2016.

## 1. Team members
There are four team members in this group. They are:

* JIANG, Xinhong
* PAN, Hao
* CHEN, Yingshu
* ZHOU, Tingting

## 2. Demo Video
A short video demonstrating main features of this game is uploaded to Vimeo at:
https://vimeo.com/194161874

## 3. Background Research
Here list three similar games in the market – Battle of Balls, Nebulous, Agar.io.

### 3.1 Battle of Balls
Battle of Balls is a cutesy but challenging real-time casual game in which you will control a ball to eat other players' balls smaller than yours around you to become the biggest one. 

* **Features**:
1)	A variety of interactive elements: Players will be able to add friends, follow players, and own their followers, which makes you the stars in the world of Battle of Balls.
2)	Spectator Mode: When the big bosses emerge, you can use Spectator mode to watch their fights and root for them
3)	Team play: It supports team play together with voice chatting, group chatting.

* **Shortcoming**: 
1)	A little user-unfriendly, for example, when playing the game, there is no button for pausing or quitting the game; the setting of board of moving area damages the sense of game scene, which really influences user experience.
2)	Does not set game difficulty level, you can last the game for very long time unless eaten by others, during which player would easily feel board.

* **Possible improvements**: 
Add some necessary buttons or labels to increase user-friendliness. Set different difficulty levels, for example, in one of levels, the player must obtain some aim weight in limited time, which is considered “pass this level”.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/11.PNG?raw=true"  width = "600" height = "360" alt="Battle of Balls" />
Battle of Balls
</center>

reference:
http://2p.com/34710267_1/Battle-of-Balls-Play-Balls-with-Players-Worldwide-by-minishop.htm

### 3.2 Nebulous
Grow the blobs by collecting dots placed throughout the game or gobbling up smaller players. Avoid bigger players attempting to do the same. Compete with other players to become the biggest blob.

* **Features**:
1)	Players can find groups, join a clan and play with friends.
2)	Over 450 skins with unique ways to unlock them and players can upload their own custom skin for other players to see.
3)	Online Multiplayer (up to 27 players per game) or Offline Single-player.
4)	Various game mode: FFA, Timed FFA, FFA Classic, Teams, Timed Teams, Capture the Flag, Survival, Soccer and Domination Modes!

* **Shortcoming**: 
An evident shortcoming similar to Battle of Balls: the setting of board of moving area damages the sense of game scene, which really influences user experience.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/22.PNG?raw=true"  width = "600" height = "360" alt="Nebulous" />
Nebulous
</center>

reference:
https://play.google.com/store/apps/details?id=software.simplicial.nebulous&hl=en

### 3.3 Agar.io 
* **Features**:
1)	Online multiplayers
2)	A variety of special secret skins with the right username
3)	Actions of splitting, shrinking and dodging tactics to catch other players

* **Shortcoming**: 
The game is a bit lagged and there are too many adds.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/33.PNG?raw=true"  width = "600" height = "360" alt="Agar" />
Agar.io
</center>

Based on above games, we develop a new game for offline single-player competing with enemies played with artificial intelligence in iOS platform by means of game engine Cocos2d-x. Also, we add more interesting playing modes and skills to our game.

## 4. Game Overview
It is an entertaining and strategy game application on philosophy of survival of the fittest.
To be the strongest species to survive, the asteroid in universe have got to be as much bigger and stronger as possible by eating other smaller ones around it in defense of attacks from enemies.



To be the very surveillance of the universe, keep poking to move, eating others to collect energy and gain weight. It is weight that can proves your ability and power. When your weight is large enough to dominate the universe, you become the king of asteroids in the universe.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/master/%E6%B8%B8%E6%88%8F%E6%88%AA%E5%9B%BE/%E5%B1%8F%E5%B9%95%E5%BF%AB%E7%85%A7%202016-12-04%2023.05.23.png?raw=true"  width = "600" height = "360" alt="game scene" />
</center>

It is your show time to protect your village using your intelligence and skills. The history records will tell you how honorable your achievement is.

## 5. Detailed Game Description
### 5.1.	Background Story
In Universe, battles never come to the end. Player is one of the bubbles in the village and willing to fight for your home. Player keeps moving to trace enemies and collect energy, player eludes quickly the bigger enemies to sustain your power, until player is powerful enough to protect the village and drive rivals away.
### 5.2.	Objective
The objective is to survive from being encroached and eliminate enemies. To be powerful enough, the hero is supposed to eat smaller ones as many as possible to gain weight and get a larger size. The hero also can use bullets to defeat demons to get higher score. The player can break the history record by eating lots of asteroids and defeating as many demons as possible. To add the challenge of the game, we set two game modes – unlimited-time and timer.  

In the unlimited-time mode, the player has to control the hero to eat other asteroids and defeat demons as many as possible. Meanwhile, the hero should avoid being encroached or attacked by the bigger ones, otherwise the game will be over. The final score will be calculated when the game is over and the highest score will be recorded.

In the timer mode, the hero tries to eat smaller ones and defeat demons as many as possible within a period of certain time. The final score will be calculated when the limited time is up or the hero dies in halfway and the highest score will be recorded.

### 5.3.	Gameplay
#### 5.3.1.	Storyboard


<center>
<img src ="http://img.blog.csdn.net/20161205230555417"  width = "600" height = "300" alt="storyboard" />
</center>

1) Booting

There is an unavoidable welcome interface showing a short period of time on the screen, displaying the game title, main characters and content.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/booting.png?raw=true"  width = "500" height = "300" alt="booting" />
Booting interface
</center>

2) Menu interface

The menu is the interface consisting main scene with animated background and several UI components, used by the player to input username, select game mode and difficulty level. Player can select “limited time” or “unlimited time” game mode, and select game levels. The initial game level is Level 1 and player has to pass the last level to unlock the next level. After inputting above info, once clicking the “Strat” button, the player will enter the game playing scene.

There is a “History” button used to skip to game history interface, which would display best game records of different game levels.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/menu.jpg?raw=true"  width = "500" height = "300" alt="menu" />
Menu interface
</center>

3) Game interface
After clicking “Start” button in the Menu interface, the game starts and the hero appears at the center of the screen. 

The background is a galaxy universe and the background will change correspondingly as the hero moves. The dynamic rival asteroids (called AI asteroids and demon asteroids) controlled by AI and static tiny particles with a certain weight are allocated here and there in the universe. The hero moving by oriented moving gestures of the player can eat smaller rivals and any tiny particles. And he rivals controlled by artificial intelligence would also do that. 

When asteroids eat others, their weights and sizes get larger, but the moving speed would be reduced. That is, the moving speed is inversely proportional to the weight while the size (radius) of the asteroid is proportional to the weight.

Here comes to a special case that hero cannot eat demon asteroids but can only shoot tiny particles to them to decrease their weights. When playing, the player can click the buttons on the bottom right of the interface -- “Shooting” and “Accelerating”. One is used to attack the demon asteroids, and the other is a special and necessary skill for the hero. When the size of hero is very large, there is no denying that the moving speed slows down and it is hard to catch the smaller ones. So hero can adopt such a strategy -- dividing itself into several asteroids to speed up moving and get more chance to eat enemies. Certainly, hero would also take more risks of being eaten by others. So considering which situation the hero should be split or merged adds challenges to this game.

The final score will be calculated according to the number of asteroids the hero ate and defeated when the game is over or time is up, and the highest score will be recorded.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/capture1.PNG?raw=true"  width = "600" height = "300" alt="menu" />
Game interface
</center>


4) Game result interface
When the game is over, game result information will pop up consisting of data of weight, time, number of rival asteroids eaten by hero. There are buttons for restarting the game and returning the menu interface.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/result.png?raw=true"  width = "600" height = "300" alt="result" />
Game interface
</center>

5) History interface
There is a table showing best game records of different levels and a button to return the menu interface.
On the menu interface, the player selects the game mode and level.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/record.PNG?raw=true"  width = "700" height = "200" alt="record" />
Game records for Unlimited mode and Timer mode
</center>

#### 5.3.2. Game Mode & Game Levels

On the menu interface, the player selects the game mode and level.

There are two game modes -- unlimited-time mode and timer mode. Levels are set from easiest to hardest for each game mode. Accordingly, the game history will record the best record of each level. In the initial state, only Level 1 is unlocked and only when the last level is passed will the following levels be unlocked. Otherwise the player cannot enter the next level. Each level is set with different prescribed playing time, target weight and AI asteroids settings. As the level of difficulties increases, target weight will be larger (in unlimited mode), the number of demons and AI asteroids will be larger, and the demons will become more sensitive as well.

In our prototype version, only game modes are taken into account. As the time passed by, the demons will be more sensitive to the hero and it will be harder to get higher score.


#### 5.3.3. The core of Gameplay
The key point of gameplay is that the single player is supposed to annihilate as many smaller asteroids as possible and avoiding being eaten. The moving speed is inversely proportional to the weight while the size (radius) of the asteroid is proportional to the weight. The shooting and speeding up skills are essential for the player to strategically utilize in order to gain a great score in the game.

#### 5.3.4. Game Difficulties
Different game levels or game difficulties lies on prescribed game time (if it is limited), number of enemies (AI asteroids), sensibility of demon asteroids, aimed weight and initial weight of AI asteroids. All these factors should be taken into consideration to break a new record of the game, flexibly using skills speeding up or shooting to escape the tracing from enemies and annihilate more other asteroids.


## 6. Programming implementation

### 6.1 Cocos2dx
Cocos2d-x is an open-source and cross platform open source free 2D game engine for mobile game development. In this app, we will use several class and methods in 
Cocos2d-x.
### 6.2 Layer
In Cocos2dx, `Layer` is a subclass of  `Node` that can receive touch events and contain any `Node` as a child, including `Sprites` and other Layer objects. In this game, the inheritance of `Layer` is as follows:


<center>
<img src ="http://img.blog.csdn.net/20161205221136204"  width = "600" height = "240" alt="Layer" />
</center>


We create two layers `MenuScene` and `GameScene` that inheritate from `Layer` and use function `createScene()` to return the scenes that contain the new created layer. Take `MenuScene` as example, we create this layer as following:
```c++
class MenuScene : Layer {
public:
    // 创建对象
    static Scene* createScene();
    // 对象初始化
    virtual bool init();
    // 安帧更新
    virtual void update(float time);
    CREATE_FUNC(MenuScene);
    // 场景退出
    void onExit();
    
    float scaleCount = 0;
    
    // 动态UI引用
    Sprite *label_title;
    MenuItemImage *item_startgame1;
    MenuItemImage *item_startgame2;
    MenuItemImage *item_history;
    Sprite *menu_bg;
    LayerColor *history_layer_bg;
    
    // History UI引用
    Label *label_history;
    Label *label_name;
    Label *label_weight;
    Label *label_demon;
    Label *label_base;
    Label *label_ai;
    
    // 添加UI
    void addUI();
    void addHistoryUI();
    
    // 事件函数
    void startGameTimer();
    void startGameUnlimited();
    void openHistory();
    void showLimitedRecord();
    void showUnLimitedRecord();
    void hideHistory();
    void updateHistory(GAME_TYPE type, __String new_name, int new_weight, int new_baseball, int new_aiball, int new_demon);
};
```

Then we use function `createScene()` to return the scene that contains this layer:

```c
Scene* MenuScene::createScene() {
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    return scene;
}
```

We use `MenuScene` for the Menu interface and `GameScene` for the Game interface.

### 6.3 Sprite
In Cocos2dx, `Sprite` is a subclass of  `Node` that can be moved, rotated, scaled, animated, and undergo other transformations. In this game, the inheritance of `Sprite` is as follows:


<center>
<img src ="http://img.blog.csdn.net/20161205222734007"  width = "600" height = "480" alt="Layer" />
</center>


#### 6.3.1 Baseball
`Baseball` is a virtual base class of all ball instances that can move and change size including playerBall, AIBall and demon. This class contains variables including position, radius, color, weight of the target ball, a `drawNode` method and a set of getters and setters.

```c
class BaseBall : public Sprite {

/** 重写函数 **/
public:

/** 内部变量和函数 **/
protected:
    Vec2 position = Vec2::ZERO;        // 坐标
    double radius = 0;                 // 半径
    Color4F color = Color4F::YELLOW;   // 颜色
    int weight = 1;                    // 重量
    bool isDraw = true;                // 是否启动图形绘制
    DrawNode *drawNode = NULL;         // DrawNode
    
/** 对外接口 **/
public:
    // getter
    const bool getIsDraw()const{return isDraw;}
    const Vec2 getPos()const{return position;}
    const float getR()const{return radius;}
    const int getBallWeight()const{return weight;}
    const Color4F getBallColor()const{return color;}
    
    // setter
    void setIsDraw(bool isdraw){isDraw = isdraw;}
    
    // 缩放
    virtual void scale(const float scale){}
};
```

#### 6.3.2 AIBall
`AIBall` is a subclass of `BaseBall` and the base class of `PlayerBall` and `Demon`. The instances of this class have the following features:
* They can eat the static ball and other AI ball instances that are smaller than themselves, including the player ball that is controlled by the player.

* They will move automatically and randomly. If the player ball is in their detectable area, they will chase the player ball if they are bigger than it and will get away from the player ball if they are smaller than it. This is realized by the method `gameObserver` in `Game.cpp` as follows:
    ```c
        for (Vector<AIBall*>::const_iterator it = AIBallArray.begin(); it != AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        AIBall *player = Game::sharedGame()->player;
        Point p = player->getPos();
        int weight = player->getBallWeight();
        // squared distance of centers of aiball and player ball
        float distance2 = pow(p.x - aiball->getPos().x, 2.0) + pow(p.y - aiball->getPos().y, 2.0);
        // distance of aiball and player ball
        float distance = sqrt(distance2) - player->getR() - aiball->getR(); 
        if (distance < ScreenHeight) {

            Vec2 dir = aiball->getPos() - p;
            
            if (aiball->getBallWeight() > weight) {
                dir = -dir + aiball->getDirection(); // chase
            }else {
                dir += aiball->getDirection(); // flee
            }
    
            dir.normalize();
            aiball->setDirection(dir);
        }
    }
    ```
* When the radius of a AI ball instance is larger than a quarter of the screen height, this ball will 'explode' and this object will be removed. 
* The AI balls will be created periodically on random positions according to the maximum number of demons and the existing number of demons in the game.

#### 6.3.3 PlayerBall
The `PlayerBall` is a subclass of `AIBall` and the instance of this class is the ball that controlled by the player. The player ball instance has the following features:
* It can eat the static ball and all AI ball instances that are smaller than itself.
* Listen touch events. When a drag event is triggered, the start point and end point of the touch event are formed a vector served as the moving direction of the player ball. If the it is a touch event only and the start point and end point of this event is too close, the player ball will be static. This is realized by the method `addTouchListener` in `Game.cpp`
* When the button of **shoot** is clicked, the `shoot` method in `Game.cpp` will be called to realize the effect that the player shoot 'bullets' in the direction of itself. The 'bullets' are used to attack the 'demons' to reduce their size and destroy them.
* When the button of **dash** is clicked, the `dash` method in `Game.cpp` will be called to realize the speed-up effect of the player ball. The dash button will be disabled after clicked and resumed after 500 frames.

#### 6.3.4 Demon
The `Demon` is a subclass of `AIBall` and the instances of this class has the following features:


* They can eat the static ball to increase size but cannot eat a smaller AI ball as the other AI ball or player ball do.
* When they collide with the player ball, the weight of player ball will be lost constantly until two balls are separate. When thay collide with the AI bal, they will be eaten if the AI ball is bigger.
* They will lose weight (reduce size) when they are 'attacked' by the bullets that are shooted from the player ball when the button of **shoot** is clicked. When their weight is reduced lower than 50, it will be killed.
* They will move automatically and randomly. If the player ball is in thier detactable area, they will chase the player ball no matter what their size are. Similarly as the AIBall, this is realized by the method `gameObserver` in `Game.cpp` as follows:
```c
 for (Vector<Demon*>::const_iterator it = DemonArray.begin(); it != DemonArray.end(); it++) {
        Demon *demon = *it;
        Vec2 newDir = player->getPos() - demon->getPos();
        if(newDir.x*newDir.x + newDir.y*newDir.y > ScreenWidth*ScreenWidth*4) continue;
        newDir.normalize();
        demon->setDirection(newDir);
    }
```
* The demon instances will be created periodically on random positions according to the maximum number of demons and the existing number of demons in the game.

### 6.4 StaticBall and Bullet
Unlike the ball class above, the `StaticBall` and `bullet` are just data structure but not classes that inheritated from the Sprite since transformations on these objects are not needed. By doing this, the production of significant number of instances is avoided and these objects are created by the `drawNode` method (`drawPolygon` for `StaticBall` and `drawDot` for `bullet`). For example, the data structure of `StaticBall` is as follows:
```c
class StaticBall {
public:
    bool isActive;                   // 是否存活
    Vec2 position = Vec2::ZERO;      // 坐标
    float radius = 0;                // 半径
    int polyNum = 3;                 // 边数
    Point *vertexs;                  // 顶点数组
    Color4F color = Color4F::YELLOW; // 颜色
    int weight = 5;                  // 重量
    
    // 构造
    StaticBall();
    // 重新激活
    void reActive();
    // 缩放
    void scale(float scale);
    // 析构
    ~StaticBall();
};
```

The `StaticBall` objects have the following features:

* They have fixed size, weight, color and position after being created. They are static and will be destroyed when they collide with all other AI balls, player balls and demons.
* Random number of static balls will be created periodically on random positions according to the maximum number of static balls and the existing number of static balls in the game.

The `bullet` objects have the following features:

* They have fixed size, color, speed and direction after being created. They will move in the directon of player ball. 
* They are used to reduce the weight of the demons and will be created when the button of shoot is clicked by the user.

### 6.5 Scaledown and Scaleup
There are a button of Scaledown and a button of Scaleup to realize the effects of zooming the camera in the game scene. These two effects are triggered when the buttons are touched and the method `scaleScreen` in `Game.cpp` is called. 

The game is scaled by:
```C
  //maxW and maxH are the width and height of the game border
  maxW *= scale;
  maxH *= scale;
```

The ball objects (including AIBall, PlayerBall, demon and StaticBall) are scaled by scaling their positions, radius, speed (no speed for the StaticBall).
```C
// postion
position *= scale;
// speed
speedInterval /= scale;
// radius
radius = sqrt(weight*scale);
```
However, the label of ball objects are not included in the scalling.

### 6.6 Draw Order
In our game, we determines which node is drawn behind or in front of another node by setting their zOrder property. The node with the smallest zOrder property is drawn first and so will be placed at the bottom. The zOrder of different labels, sprites and layers in our game are as follows:

* Background: -100001
* Static Ball: -100000
* Bullet: -100000
* Uilayer and all buttons on Game Scene: 100000
* AIBall, PlayerBall, Demon: from -100000 to 0, larger ball has larger zOrder. This is realized by the following,
```C
drawNode->setGlobalZOrder(radius-100000);
```

By doing this, the background will be placed so that every other objects are above it and the buttons are placed at the highest layer so that will not be coverd by the balls. The bigger ball will have larger zOrder so that it will always on the top of the smaller ball.


## 7. Optimization Algorithm
### 7.1 Rendering
In this game, we will only render the objects including AI balls, demons and static balls that are within the screen to improve the fps of the game. Take the `draw` method of `AIBall` as example and code is following: 
```c
void AIBall::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {

    // 超出屏幕不渲染 Not render balls that are out of the screen
    Vec2 playerP = Game::sharedGame()->getPlayer()->getPos();
    if(abs(position.x - playerP.x) > (ScreenWidth/2+radius) || abs(position.y - playerP.y) > (ScreenHeight/2+radius)) return;
    
    // 清空之前的绘制
    drawNode->clear();
    if (isDraw) {
        // 绘制实心圆形
        drawNode->drawDot(Vec2(0, 0), radius, color);
        drawNode->drawDot(Vec2(0, 0), radius*0.9, Color4F(1.0, 1.0, 1.0, 0.2));
        drawNode->drawCircle(Vec2(0, 0), radius, 360, radius, false, Color4F(color.r, color.g, color.b, 0.5));
        // 根据球的半径更新当前球的绘制深度，半径越大的绘制在前面覆盖更小的球
        drawNode->setGlobalZOrder(radius-100000);
    }
}
```

### 7.2 Quadtree

In our application, the collision detection will be conducted by checking all objects stored in a 1-D array. For example, for the player ball only, it need to check all static ball objects and all AI ball objects for collision detection. 

One possible way to reduce the number of checks is to use a quadtree as the data stucture to store the ball objects. The basic idea of this algorithm is to use a quadtree to divide a 2D region into more manageable parts and skip the detection among the pairs that are in two distant parts.

Each node in the quadtree represent a certain area in the 2D region and this area can be divided into four sub-areas that representd by four subnodes of this node. Each object that we need to do the detection will then be put into one of these subnodes according to where it lies in the 2D region. Then, we can skip the  detection among the pairs of objects that are in two distant parts, for intance, the objects in the top-left node cannot be colliding with the objects in the bottom-right node.

<center>
<img src ="https://github.com/jiangxh1992/PlanetWar/blob/main_from_ph/Image/quadtree.png?raw=true"  width = "240" height = "240" alt="quadtree" />
quadtree
</center>