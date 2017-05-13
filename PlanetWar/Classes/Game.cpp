//
//  Game.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//  1.层级说明：UI层（100000），Ball层（-100000~0）， 背景层（<-1000000）
//
//

#include "Game.h"
#include "BaseBall.h"
#include "AIBall.h"
#include "MenuScene.h"
#include <SimpleAudioEngine.h>

//转换成string类型
template<typename T>
string Convert2String(const T &value)
{
    stringstream ss;
    ss << value;
    return ss.str();
}

/**
 * 创建游戏场景
 */
Scene* Game::createScene(GAME_TYPE type) {
    auto scene = Scene::create();
    auto layer = Game::create(type);
    layer->curScene = scene;
    scene->addChild(layer);
    return scene;
}

Game* Game::create(GAME_TYPE type) {
    Game *game = new Game;
    game->gameType = type;
    if (game && game->init()) {
        game->autorelease();
        return game;
    }
    CC_SAFE_DELETE(game);
    return NULL;
}

/** 游戏场景单例 **/
static Game *game;
Game* Game::sharedGame() {
    if (game) {
        return game;
    }
    return NULL;
}

# pragma mark -生命周期
/**
 * 游戏初始化
 */
bool Game::init() {
    
    if (!Layer::init()) {
        return false;
    }
    game = this;
    
    // 添加颜色库
    initColorArray();
    // 游戏变量初始化
    initData();
    // 添加UI
    addUI();
    // 添加角色
    addRoles();
    
    // 开启玩家触屏交互
    addTouchListener();
    
    // 按帧更新
    this->scheduleUpdate();
    // 开启计时器
    this->schedule(schedule_selector(Game::gametimer), 1.0);
    // 开启定时器
    this->schedule(schedule_selector(Game::createBaseBallTimer), 3.0);
    // 开启AI干预
    this->schedule(schedule_selector(Game::gameObserver), 1.5);
    
    return true;
}

/**
 * 图形绘制
 */
void Game::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
    // 清空之前的绘制
    drawNode->clear();
    
    // 绘制baseball
    for (int i = 0 ; i < maxBaseBallNum ; i++) {
        StaticBall ball = staticArray[i];
        if (!ball.isActive) continue;
        // 超出屏幕不渲染
        if(abs(ball.position.x - player->getPos().x) > ScreenWidth/2 || abs(ball.position.y - player->getPos().y) > ScreenHeight/2) continue;
        // 绘制多边形
        drawNode->drawPolygon(ball.vertexs, ball.polyNum, ball.color, 1, ball.color); // 实心
        drawNode->drawPoly(ball.vertexs, ball.polyNum, true, Color4F(1, 1, 1, 0.5+CCRANDOM_0_1()*0.5));             // 空心
        //drawNode->drawDot(staticArray[i].position, staticArray[i].radius, staticArray[i].color);
        // 深度
        drawNode->setGlobalZOrder(-100000);
    }
    
    // 绘制边界
    drawNode->drawPoly(Vertexs, 4, true, Color4F(255*CCRANDOM_0_1(), 0, 0, 1.0));
    // 深度
    drawNode->setGlobalZOrder(-100000);
    
    // 绘制子弹
    for (int i =0; i < bulletArray.size(); i++) {
        if (bulletArray[i].getPos().x >= maxW || bulletArray[i].getPos().x <= -maxW || bulletArray[i].getPos().y >= maxH || bulletArray[i].getPos().y <= -maxH) {
            // 销毁子弹
            //autoreleasepool.push_back(bullet);
            bulletArray.erase(bulletArray.begin() + i);
        }else {
            // 绘制
            drawNode->drawDot(bulletArray[i].getPos(), bulletArray[i].getRadius(), bulletArray[i].getColor());
            drawNode->drawDot(bulletArray[i].getPos(), bulletArray[i].getRadius(), Color4F(1.0, 1.0, 1.0, 0.8));
            // 深度
            drawNode->setGlobalZOrder(-100000);
            // 移动
            bulletArray[i].move();
        }
    }
}

// 安帧更新
void Game::update(float time) {
    
    // 加速功能恢复
    if (dashCount > 0) {
        dashCount -= 0.2;
        dashTimer->setPercentage(dashCount);
    }
    
    // left
    debuglabel->setString("interval:"+Convert2String(player->getSpeedInterval()));
    label_weight->setString("weight:"+Convert2String(player->getBallWeight()));
    label_scale->setString("scale:"+Convert2String(scale));
    
    // right
    label_ainum->setString("AIBall:"+Convert2String(player->getEatAINum())+" | "+Convert2String((int)AIBallArray.size()));
    label_basenum->setString("BaseBall:"+Convert2String(player->getEatBaseNum())+" | "+Convert2String(baseNum));
    label_demon->setString("Demon:"+Convert2String(kill)+" | "+Convert2String((int)DemonArray.size()));
    
}

/**
 * 游戏观察者
 */
void Game::gameObserver(float delta) {
    if(!player->isVisible()) return;
    // AIBall 躲避或追逐player
    for (Vector<AIBall*>::const_iterator it = AIBallArray.begin(); it != AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        AIBall *player = Game::sharedGame()->player;
        Point p = player->getPos();
        int weight = player->getBallWeight();
        float distance2 = pow(p.x - aiball->getPos().x, 2.0) + pow(p.y - aiball->getPos().y, 2.0);
        float distance = sqrt(distance2) - player->getR() - aiball->getR();
        if (distance < ScreenHeight) {
            // 降低AI灵敏度
            //if(CCRANDOM_0_1() < 0.2) break;
            Vec2 dir = aiball->getPos() - p;
            
            if (aiball->getBallWeight() > weight) {
                dir = -dir + aiball->getDirection(); // 追逐
            }else {
                dir += aiball->getDirection(); // 躲避
            }
            
            dir.normalize();
            aiball->setDirection(dir);
        }
    }
    
    // DemonBall主动攻击player
    for (Vector<Demon*>::const_iterator it = DemonArray.begin(); it != DemonArray.end(); it++) {
        Demon *demon = *it;
        // 降低AI灵敏度
        //if(CCRANDOM_0_1() < 0.5) break;
        Vec2 newDir = player->getPos() - demon->getPos();
        if(newDir.x*newDir.x + newDir.y*newDir.y > ScreenWidth*ScreenWidth*4) continue;
        newDir.normalize();
        demon->setDirection(newDir);
    }
    
}

/**
 * 计时器
 */
void Game::gametimer(float delta) {
    
    if (gameType == GAME_TIMER) {
        --timeCount;
        // 游戏结束
        if(timeCount <= 0)
            gameOver();
    }else if (gameType == GAME_UNLIMITED) {
        ++timeCount;
    }
    
    int minute = timeCount/60;
    int seconds = timeCount%60;
    __String s;
    s.initWithFormat("%02d:%02d",minute,seconds);
    label_time->setString(s._string);
    
}

/**
 * 游戏结束
 */
void Game::gameOver() {
    
    // 1.游戏结束处理工作
    isGameOver = true;
    // 停止交互
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    // 停止计时
    this->unschedule(schedule_selector(Game::gametimer));
    // 游戏结束音效
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music_gameover.mp3", true);
    
    // 2.游戏数据提取整理更新
    string name = player->label_tag->getString();     // 名字
    int new_weight = player->getBallWeight();         // 体重
    int new_demon = kill;                             // 杀死demon数量
    int new_baseball = player->getEatBaseNum();           // 吞并baseball数量
    int new_aiball =  player->getEatAINum();              // 吞并AIBall数量
    bool result = updateData(name, new_weight, new_baseball, new_aiball, new_demon);
    
    // 3.显示游戏结束对话框
    // 对话框层
    LayerColor *gameover_layer_bg = LayerColor::create(Color4B(0, 0, 0, 200), ScreenWidth, ScreenHeight);
    gameover_layer_bg->setPosition(Vec2(0, 0));
    uilayer->addChild(gameover_layer_bg, 100001);
    Node *gameover_layer = Node::create();
    gameover_layer->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    gameover_layer_bg->addChild(gameover_layer);
    
    // 对话框背景
    Sprite *dialog_box = Sprite::create("dialog_box.png");
    dialog_box->setAnchorPoint(Vec2(0.5, 0.5));
    dialog_box->setPosition(Vec2(0, 0));
    gameover_layer->addChild(dialog_box,100001);
    
    // 卡通人物
    Sprite *character = Sprite::create(result ? "character_win.png" : "character_lose.png");
    character->setAnchorPoint(Vec2(1, 0.5));
    character->setPosition(Vec2(-100, 50));
    gameover_layer->addChild(character,100001);
    
    // 内容背景
    int contentW = ScreenWidth/2-20;
    int contentH = ScreenHeight/2-20;
    int marginTop = 40;
    int marginLeft = 30;
    LayerColor *content_layer = LayerColor::create(Color4B(255, 255, 255, 0), contentW, contentH);
    content_layer->setIgnoreAnchorPointForPosition(false);
    content_layer->setAnchorPoint(Vec2(0, 0.5));
    content_layer->setPosition(Vec2(-80, 20));
    gameover_layer->addChild(content_layer,100001);
    
    Label *gameover = Label::create();
    gameover->setString(result ? "BEST RECORD!" : "GAME OVER!");
    gameover->setSystemFontName(FontPlanet);
    gameover->setSystemFontSize(15);
    gameover->setAnchorPoint(Vec2(0.5, 1));
    gameover->setPosition(contentW/2, contentH-5);
    content_layer->addChild(gameover,100001);
    
    Label *label_name = Label::create();
    label_name->setString("Name:"+name);
    label_name->setSystemFontName(FontPlanet);
    label_name->setAnchorPoint(Vec2(0, 1));
    label_name->setPosition(marginLeft, contentH-marginTop);
    content_layer->addChild(label_name,100001);
    
    int labelH = label_name->getContentSize().height+3;
    
    Label *label_weight = Label::create();
    string score = gameType == GAME_TIMER ? "Weight:"+Convert2String(new_weight) : "Score:"+Convert2String(new_baseball + new_aiball*10 + new_demon*15);
    label_weight->setString(score);
    label_weight->setSystemFontName(FontPlanet);
    label_weight->setAnchorPoint(Vec2(0, 1));
    label_weight->setPosition(marginLeft, contentH-marginTop-labelH);
    content_layer->addChild(label_weight,100001);
    Label *label_demon = Label::create();
    label_demon->setString("Kill Demon:"+Convert2String(new_demon));
    label_demon->setSystemFontName(FontPlanet);
    label_demon->setAnchorPoint(Vec2(0, 1));
    label_demon->setPosition(marginLeft, contentH-marginTop-labelH*2);
    content_layer->addChild(label_demon,100001);
    Label *label_base = Label::create();
    label_base->setString("Eat BaseBall:"+Convert2String(new_baseball));
    label_base->setSystemFontName(FontPlanet);
    label_base->setAnchorPoint(Vec2(0, 1));
    label_base->setPosition(marginLeft, contentH-marginTop-labelH*3);
    content_layer->addChild(label_base,100001);
    Label *label_ai = Label::create();
    label_ai->setString("Eat AIBall:"+Convert2String(new_aiball));
    label_ai->setSystemFontName(FontPlanet);
    label_ai->setAnchorPoint(Vec2(0, 1));
    label_ai->setPosition(marginLeft, contentH-marginTop-labelH*4);
    content_layer->addChild(label_ai,100001);
    
    // 按钮
    auto item_continue = MenuItemImage::create("btn_continue_normal.png", "btn_continue_pressed.png", CC_CALLBACK_1(Game::reStartGame, this));
    item_continue->setAnchorPoint(Vec2(1, 1));
    item_continue->setPosition(Vec2(-10, 0));
    auto item_back = MenuItemImage::create("btn_menu_normal.png", "btn_menu_pressed.png", CC_CALLBACK_1(Game::back, this));
    item_back->setAnchorPoint(Vec2(0, 1));
    item_back->setPosition(Vec2(10, 0));
    
    // 按钮菜单
    auto menu = Menu::create(item_continue, item_back,NULL);
    menu->setOpacity(200);
    menu->setPosition(Vec2(0, -contentH/2));
    gameover_layer->addChild(menu,100001);
    
}

/**
 * 析构函数
 */
Game::~Game(){
    this->unscheduleUpdate();
    this->unscheduleAllCallbacks();
    this->removeAllChildren();
}

#pragma mark -工具函数

Color4F convert2F(Color4B colorb) {
    return Color4F(colorb.r, colorb.g, colorb.b, 1);
}

void Game::initColorArray() {
    ColorArray[0] = convert2F(Color4B(244, 170, 83, 1));
    ColorArray[1] = convert2F(Color4B(240, 135, 70, 1));
    ColorArray[2] = convert2F(Color4B(73, 180, 162, 1));
    ColorArray[3] = convert2F(Color4B(222, 93, 255, 1));
    ColorArray[4] = convert2F(Color4B(251, 79, 251, 1));
    ColorArray[5] = convert2F(Color4B(244, 188, 53, 1));
    ColorArray[6] = convert2F(Color4B(253, 80, 108, 1));
    ColorArray[7] = convert2F(Color4B(89, 205, 124, 1));
    ColorArray[8] = convert2F(Color4B(245, 173, 88, 1));
    ColorArray[9] = convert2F(Color4B(255, 70, 144, 1));
    ColorArray[10] = convert2F(Color4B(91, 212, 81, 1));
    ColorArray[11] = convert2F(Color4B(242, 83, 80, 1));
    ColorArray[12] = convert2F(Color4B(166, 214, 76, 1));
    ColorArray[13] = convert2F(Color4B(237, 98, 67, 1));
    ColorArray[14] = convert2F(Color4B(255, 136, 194, 1));
    ColorArray[15] = convert2F(Color4B(252, 210, 0, 1));
    ColorArray[16] = convert2F(Color4B(255, 164, 136, 1));
    ColorArray[17] = convert2F(Color4B(255, 187, 102, 1));
    ColorArray[18] = convert2F(Color4B(255, 221, 85, 1));
    ColorArray[19] = convert2F(Color4B(255, 255, 119, 1));
    ColorArray[20] = convert2F(Color4B(221, 255, 119, 1));
    ColorArray[21] = convert2F(Color4B(187, 255, 102, 1));
    ColorArray[22] = convert2F(Color4B(102, 255, 102, 1));
    ColorArray[23] = convert2F(Color4B(119, 255, 204, 1));
    ColorArray[24] = convert2F(Color4B(176, 136, 255, 1));
    ColorArray[25] = convert2F(Color4B(210, 142, 255, 1));
    ColorArray[26] = convert2F(Color4B(227, 119, 255, 1));
    ColorArray[27] = convert2F(Color4B(255, 119, 255, 1));
    ColorArray[28] = convert2F(Color4B(228, 96, 132, 1));
    ColorArray[29] = convert2F(Color4B(153, 153, 255, 1));
    /*
    254, 76, 64
    253, 185, 51
    0, 235, 192
    */
    NameArray[0] = "爱吃大米的小老鼠";
    NameArray[1] = "萌萌的橘子";
    NameArray[2] = "叶子姑娘";
    NameArray[3] = "深海大鲨鱼";
    NameArray[4] = "小虾米";
    NameArray[5] = "不要吃我";
    NameArray[6] = "无敌小正太";
    NameArray[7] = "深山野狼";
    NameArray[8] = "樱桃小丸子";
    NameArray[9] = "鼓眼睛";
}

/**
 * 游戏变量初始化
 */
void Game::initData() {
    
    // 游戏时间
    timeCount = (gameType == GAME_TIMER) ? maxSeconds : 0;
    // baball个数
    baseNum = maxBaseBallNum;
    
    // 默认不缩放
    scale = 1.0f;
    
    // 默认游戏状态
    //CurState = IDLE_NORMAL;
    
    // 对象容器初始化
    AIBallArray = Vector<AIBall*>();
    DemonArray = Vector<Demon*>();
    
    // 边界顶点数组
    updateVertexs();
}

/**
 * 添加UI
 */
void Game::addUI() {
    
    // 开场背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music_game_bg.mp3", true);
    
    // drawnode
    drawNode = DrawNode::create();
    addChild(drawNode);
    
    // 背景层
    bglayer2 = Sprite::create("game_galaxy.jpg");
    bglayer2->setScale(2.5);
    bglayer2->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    addChild(bglayer2);
    bglayer2->setGlobalZOrder(-1000001);
    
    bglayer1 = LayerColor::create(Color4B(0, 0, 0, 150), maxW*3, maxH*3);//102, 102, 153
    bglayer1->setIgnoreAnchorPointForPosition(false);
    bglayer1->setAnchorPoint(Vec2(0.5, 0.5));
    bglayer1->setPosition(Vec2(0, 0));
    addChild(bglayer1);
    bglayer1->setGlobalZOrder(-1000000);
    
    // UI层
    uilayer = LayerColor::create(Color4B(0, 0, 0, 0), ScreenWidth, ScreenHeight);
    addChild(uilayer);
    uilayer->setGlobalZOrder(100000);
    // 粒子
    ParticleSystemQuad *explode = ParticleSystemQuad::create("particle_bg.plist");
    explode->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    explode->setGlobalZOrder(-100001);
    uilayer->addChild(explode);
    // 云层
    auto menu_cloud = Sprite::create("menu_cloud.png");
    menu_cloud->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    menu_cloud->setOpacity(150);
    //uilayer->addChild(menu_cloud);
    
    // left
    debuglabel = Label::create();
    debuglabel->setString("0");
    debuglabel->setAnchorPoint(Vec2(0, 1));
    debuglabel->setPosition(Vec2(75,ScreenHeight));
    debuglabel->setGlobalZOrder(100000);
    uilayer->addChild(debuglabel);
    
    label_weight = Label::create();
    label_weight->setString("weight");
    label_weight->setAnchorPoint(Vec2(0, 1));
    label_weight->setPosition(Vec2(75, ScreenHeight - debuglabel->getContentSize().height));
    label_weight->setGlobalZOrder(100000);
    uilayer->addChild(label_weight);
    
    label_scale = Label::create();
    label_scale->setString("scale");
    label_scale->setAnchorPoint(Vec2(0, 1));
    label_scale->setPosition(Vec2(75, ScreenHeight - label_scale->getContentSize().height*2));
    label_scale->setGlobalZOrder(100000);
    uilayer->addChild(label_scale);
    
    // center
    label_time = Label::create();
    label_time->setString("00:00");
    label_time->setAnchorPoint(Vec2(0.5, 1));
    label_time->setPosition(ScreenWidth/2, ScreenHeight);
    label_time->setGlobalZOrder(100000);
    uilayer->addChild(label_time);
    
    // right
    label_ainum = Label::create();
    label_ainum->setString("ainum");
    label_ainum->setAnchorPoint(Vec2(0, 1));
    label_ainum->setPosition(Vec2(ScreenWidth/3*2,ScreenHeight));
    label_ainum->setGlobalZOrder(100000);
    uilayer->addChild(label_ainum);
    
    label_basenum = Label::create();
    label_basenum->setString("basenum");
    label_basenum->setAnchorPoint(Vec2(0, 1));
    label_basenum->setPosition(Vec2(ScreenWidth/3*2,ScreenHeight - label_basenum->getContentSize().height));
    label_basenum->setGlobalZOrder(100000);
    uilayer->addChild(label_basenum);
    
    label_demon = Label::create();
    label_demon->setString("demon");
    label_demon->setAnchorPoint(Vec2(0, 1));
    label_demon->setPosition(ScreenWidth/3*2,ScreenHeight - label_basenum->getContentSize().height*2);
    label_demon->setGlobalZOrder(100000);
    uilayer->addChild(label_demon);
    
    // 绘制屏幕中心
    auto centerLabel = Label::create();
    centerLabel->setString("+");
    centerLabel->setTextColor(Color4B(255, 255, 255, 100));
    centerLabel->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    uilayer->addChild(centerLabel);
    centerLabel->setGlobalZOrder(100000);
    
    // 按钮菜单
    // 1.返回按钮
    auto item_back = MenuItemImage::create("button_back.jpg", "button_back.jpg", CC_CALLBACK_1(Game::back, this));
    item_back->setPosition(Vec2(VisiableSize.width+50 - item_back->getContentSize().width/2, VisiableSize.height - item_back->getContentSize().height/2));
    //item_back->setGlobalZOrder(100000);
    item_back->setLocalZOrder(100000);
    
    // 2.加速按钮
    auto item_dash = MenuItemImage::create("button_dash_normal.jpg", "button_dash_pressed.jpg", CC_CALLBACK_1(Game::dash, this));
    item_dash->setAnchorPoint(Vec2(1,0));
    item_dash->setPosition(Vec2(ScreenWidth-80, 50));
    item_dash->setGlobalZOrder(100000);
    dashTimer = ProgressTimer::create(Sprite::create("button_dash_process.jpg"));
    dashTimer->setAnchorPoint(Vec2(0, 0));
    dashTimer->setPosition(Vec2(0,0));
    dashTimer->setPercentage(dashCount);
    item_dash->addChild(dashTimer);
    
    // 3.发射按钮
    auto item_shoot = MenuItemImage::create("button_shoot_normal.jpg", "button_shoot_pressed.jpg", CC_CALLBACK_1(Game::shoot, this));
    item_shoot->setAnchorPoint(Vec2(1,0));
    item_shoot->setPosition(Vec2(ScreenWidth - item_dash->getContentSize().width -90, 20));
    item_shoot->setGlobalZOrder(100000);
    // 4.缩放按钮
    auto item_scaleup = MenuItemImage::create("button_add.jpg", "button_add.jpg", CC_CALLBACK_1(Game::scaleup, this));
    item_scaleup->setAnchorPoint(Vec2(0, 0));
    item_scaleup->setPosition(Vec2(0, 0));
    item_scaleup->setGlobalZOrder(100000);
    auto item_scaledown = MenuItemImage::create("button_sub.jpg", "button_sub.jpg", CC_CALLBACK_1(Game::scaledown, this));
    item_scaledown->setAnchorPoint(Vec2(0, 0));
    item_scaledown->setPosition(Vec2(0, item_scaledown->getContentSize().height));
    item_scaledown->setGlobalZOrder(100000);
    // 按钮菜单
    menu = Menu::create(item_back, item_dash, item_shoot, item_scaleup, item_scaledown, NULL);
    menu->setOpacity(200);
    menu->setPosition(Vec2::ZERO);
    menu->setGlobalZOrder(100000);
    uilayer->addChild(menu);
    
}

void Game::addRoles() {
    // 静态baseball
    createBallFactory(BALL_BASE, maxBaseBallNum);
    // 动态AIBall
    createBallFactory(BALL_AI, maxAIBallNum);
    // Demon
    createBallFactory(BALL_DEMON, 2);
    
    // 创建玩家
    player = PlayerBall::create();
    player->setLabel("WD蜂");
    player->setSpeedFactor(0);
    addChild(player);
}

/**
 * Ball工厂函数
 */
void Game::createBallFactory(FACTORY_TYPE type, int num) {
    switch (type) {
        case BALL_BASE:
            createBaseBalls(num);
            break;
        case BALL_AI:
            createAIBAlls(num);
            break;
        case BALL_DEMON:
            createDemonBalls(num);
            break;
        case BALL_BULLET:
            createBullet();
        default:
            break;
    }
}

void Game::createBaseBalls(int num) {
    staticArray = new StaticBall[num];
    for (int i = 0; i<num; i++) {
        staticArray[i] = StaticBall();
    }
}

void Game::createBullet() {
    Vec2 position = player->getPos();
    Vec2 direction = player->getDirection();
    int power = 50;
    Color4F color = player->getBallColor();
    PlayerBullet bullet;
    bullet.setPosition(position);
    bullet.setDirction(direction);
    bullet.setPower(power);
    bullet.setColor(color);
    bullet.setSpeed(6);
    bullet.setRadius(3);
    bulletArray.push_back(bullet);
}

void Game::createAIBAlls(int num) {
    for (int i = 0 ; i<num ; i++) {
        auto aiball = AIBall::create();
        int index = CCRANDOM_0_1()*9;
        aiball->setLabel(NameArray[index]);
        addChild(aiball);
        AIBallArray.pushBack(aiball);
    }
}

void Game::createDemonBalls(int num) {
    for (int i = 0; i < num ; i++) {
        auto demon = Demon::create();
        demon->setLabel("恶魔");
        addChild(demon);
        DemonArray.pushBack(demon);
    }
}

/**
 * 定时生成小球和AIBall
 */
void Game::createBaseBallTimer(float delta) {
    // 随机数
    float random = CCRANDOM_0_1();
    // 小球随机激活
    for (int i = 0; i<maxBaseBallNum; i++) {
        bool pass = (random < 0.3) ? true : false;
        if (pass && !staticArray[i].isActive) {
            staticArray[i].reActive();
            baseNum++;
        }
    }
    // AIBall
    int createNum = maxAIBallNum - (int)AIBallArray.size();
    if (createNum > 0) {
        createBallFactory(BALL_AI, createNum);
    }
    
    // Demon
    if (random < 0.2 && DemonArray.size()<5) {
        createBallFactory(BALL_DEMON, 1);
    }
}

/**
 * 屏幕缩放
 */
void Game::scaleScreen(float scale) {
    
    this->scale *= scale;
    // 场景缩放
    maxW *= scale;
    maxH *= scale;
    updateVertexs();
    
    // 缩放静止的球
    for (int i = 0 ; i < maxBaseBallNum ; i++) {
        staticArray[i].scale(scale);
    }
    
    // 缩放AIBall
    for (Vector<AIBall*>::const_iterator it = AIBallArray.begin(); it != AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        aiball->scale(scale);
    }
    
    // 缩放demon
    for (Vector<Demon*>::const_iterator it = DemonArray.begin(); it != DemonArray.end(); it++) {
        Demon *demon = *it;
        demon->scale(scale);
    }
    
    // 缩放player
    player->scale(scale);
    
}

void Game::addParticle(string filename, cocos2d::Vec2 position) {
    ParticleSystemQuad *explode = ParticleSystemQuad::create(filename);
    explode->setPosition(position);
    addChild(explode);
}

void Game::updateVertexs() {
    int borderX = maxW;
    int borderY = maxH;
    Vertexs[0] = Vec2(borderX, borderY);
    Vertexs[1] = Vec2(borderX, -borderY);
    Vertexs[2] = Vec2(-borderX, -borderY);
    Vertexs[3] = Vec2(-borderX, borderY);
}

bool Game::updateData(string name, int new_weight, int new_baseball, int new_aiball, int new_demon) {
    if (gameType == GAME_TIMER) {
        // 取出旧数据
        int weight = UserDefault::getInstance()->getIntegerForKey("timer_weight", -1);
        //int demon = UserDefault::getInstance()->getIntegerForKey("timer_demon", -1);
        //int baseball = UserDefault::getInstance()->getIntegerForKey("timer_baseball",-1);
        //int aiball = UserDefault::getInstance()->getIntegerForKey("timer_aiball",-1);
        // 存入新记录数据
        if (new_weight > weight) {
            UserDefault::getInstance()->setStringForKey("timer_name", name);
            UserDefault::getInstance()->setIntegerForKey("timer_weight", new_weight);
            UserDefault::getInstance()->setIntegerForKey("timer_demon", new_demon);
            UserDefault::getInstance()->setIntegerForKey("timer_baseball", new_baseball);
            UserDefault::getInstance()->setIntegerForKey("timer_aiball", new_aiball);
            return true;
        }
        return false;
    }
    else if (gameType == GAME_UNLIMITED) {
        // 取出旧数据
        //int weight = UserDefault::getInstance()->getIntegerForKey("unlimited_weight", -1);
        int demon = UserDefault::getInstance()->getIntegerForKey("unlimited_demon", -1);
        int baseball = UserDefault::getInstance()->getIntegerForKey("unlimited_baseball",-1);
        int aiball = UserDefault::getInstance()->getIntegerForKey("unlimited_aiball",-1);
        // 成绩加权
        int power = baseball + aiball*10 + demon*15;
        int new_power = new_baseball + new_aiball*10 + demon*15;
        // 存入新记录数据
        if (new_power > power) {
            UserDefault::getInstance()->setStringForKey("unlimited_name", name);
            UserDefault::getInstance()->setIntegerForKey("unlimited_weight", new_weight);
            UserDefault::getInstance()->setIntegerForKey("unlimited_demon", new_demon);
            UserDefault::getInstance()->setIntegerForKey("unlimited_baseball", new_baseball);
            UserDefault::getInstance()->setIntegerForKey("unlimited_aiball", new_aiball);
            return true;
        }
        return false;
    }
}

# pragma mark -事件函数
/**
 * 返回到菜单
 */
void Game::back(cocos2d::Ref* pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_click.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene()));
}

/**
 * 加速
 */
void Game::dash(cocos2d::Ref *pSender) {
    if(dashCount > 0) return;
    dashTimer->setPercentage(100);
    dashCount = 100;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_dash.mp3");
    player->speedUp();
}

void Game::shoot(cocos2d::Ref *pSender) {
    // 子弹音效
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
    createBallFactory(BALL_BULLET, 0);
}

/**
 * 缩放
 */
void Game::scaleup(cocos2d::Ref *pSender) {
    scaleScreen(0.9);
}

void Game::scaledown(cocos2d::Ref *pSender) {
    scaleScreen(1.1);
}

void Game::demonKilled(Demon *demon) {
    kill++;          //  杀死一个demon
    // 游戏时间增加
    if (gameType == GAME_TIMER) {
        timeCount += 20;
    }
    // 音效
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_explode.mp3");
    // 爆炸粒子
    addParticle("particle_explode.plist", demon->getPos());
    // 移除demon
    DemonArray.eraseObject(demon);
    removeChild(demon);
}

void Game::playerKilled() {
    // 震动
    CocosDenshion::SimpleAudioEngine::getInstance()->vibrate();
    // 隐藏
    player->setVisible(false);
    player->setSpeedFactor(0);
    player->setIsActive(false);
    // 复活或者游戏结束
    if(gameType == GAME_TIMER) {
        // 延迟复活
        DelayTime *delay = DelayTime::create(3);
        CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Game::playerReactive, this));
        Sequence *action = Sequence::create(delay,fun, NULL);
        runAction(action);
    }else {
        gameOver();
    }
    
}

void Game::playerReactive() {
    player->updateWeight(minWeight-player->getBallWeight());// 恢复为最小体重
    player->startProtectPlayer(); // 无敌状态
}

void Game::reStartGame(Ref* pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_click.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, Game::createScene(gameType)));
}

void Game::dashFinished() {
    //dashCount = 100;
}

#pragma mark -触屏事件

void Game::addTouchListener() {

    // 定义事件分发
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    auto oneTouch = EventListenerTouchOneByOne::create();
    // 触摸开始
    oneTouch->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan,this);
    // 触摸拖动
    oneTouch->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved,this);
    // 触摸结束
    oneTouch->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded,this);
    // 触摸取消
    oneTouch->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled,this);
    
    eventDispatcher->addEventListenerWithSceneGraphPriority(oneTouch,this);
    
}

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    // 触摸起点
    startPoint = touch->getLocation();
    // 触点坐标转换
    Vec2 p = startPoint + player->getPos() - Vec2(ScreenWidth/2, ScreenHeight/2);
    // 粒子特效
    addParticle("particle_touch.plist", p);
    return true;
}

void Game::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cout<<"moved"<<endl;
}

void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    // 触摸终点
    endPoint = touch->getLocation();
    // 触点坐标转换
    //endPoint += player->getPos() - Vec2(ScreenWidth/2, ScreenHeight/2);
    // 更新玩家移动方向
    Vec2 newDir = endPoint - startPoint;
    Vec2 center = Vec2(ScreenWidth/2, ScreenHeight/2);// 屏幕坐标系中心
    double D2 = pow(endPoint.x - center.x, 2.0) + pow(endPoint.y - center.y, 2.0);
    double R2 = pow(player->getR(), 2.0);
    bool isTouchPlayer = D2 < R2 ? true : false;
    if (abs(newDir.x) > 0.01f && abs(newDir.y) > 0.01f) { // 滑动距离足够长
        // 粒子特效
        Vec2 p = endPoint + player->getPos() - Vec2(ScreenWidth/2, ScreenHeight/2);
        addParticle("particle_touch.plist", p);
        newDir.normalize();
        player->setDir(newDir);
        player->setSpeedFactor(1.0);
    }else if(isTouchPlayer) {
        player->setSpeedFactor(0);//点击了player，此时应让player停止运动
    }
    else {
        // 此时player朝向触点移动
        newDir = endPoint - center;
        newDir.normalize();
        player->setDir(newDir);
        player->setSpeedFactor(1.0);
    }
}

void Game::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cout<<"cancelled"<<endl;
}
