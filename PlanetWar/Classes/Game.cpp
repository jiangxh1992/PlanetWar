//
//  Game.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//
#define dashTime 5 // 加速时间

#include "Game.h"
#include "BaseBall.h"
#include "AIBall.h"
#include "MenuScene.h"
using namespace std;

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
Scene* Game::createScene() {
    auto scene = Scene::create();
    auto layer = Game::create();
    layer->curScene = scene;
    scene->addChild(layer);
    return scene;
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
    this->schedule(schedule_selector(Game::createBaseBallTimer), 5.0);
    // 开启AI干预
    this->schedule(schedule_selector(Game::gameObserver), 2.0);
    
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
        // 绘制多边形
        //drawNode->drawPoly(ball.vertexs, ball.polyNum, true, ball.color);           // 空心
        drawNode->drawPolygon(ball.vertexs, ball.polyNum, ball.color, 1, ball.color); // 实心
        //drawNode->drawDot(staticArray[i].position, staticArray[i].radius, staticArray[i].color);
        // 深度
        drawNode->setGlobalZOrder(-1);
    }
    
    // 绘制边界
    drawNode->drawPoly(Vertexs, 4, true, Color4F(255*CCRANDOM_0_1(), 0, 0, 1.0));
}

// 安帧更新
void Game::update(float time) {
    
    // left
    debuglabel->setString("interval:"+Convert2String(player->getSpeedInterval()));
    label_weight->setString("wieght:"+Convert2String(player->getBallWeight()));
    label_scale->setString("scale:"+Convert2String(scale));
    
    // right
    label_ainum->setString("AIBall:"+Convert2String(player->getEatAINum())+" <- "+Convert2String((int)AIBallArray.size()));
    label_basenum->setString("BaseBall:"+Convert2String(player->getEatBaseNum())+" <- "+Convert2String(baseNum));
    label_demon->setString("Demon:"+Convert2String((int)DemonArray.size()));
    
}

/**
 * 游戏观察者
 */
void Game::gameObserver(float delta) {
    
    // AIBall 躲避或追逐player
    for (Vector<AIBall*>::const_iterator it = AIBallArray.begin(); it != AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        AIBall *player = Game::sharedGame()->player;
        if (aiball == player) {
            continue;
        }
        Point p = player->getPos();
        int weight = player->getBallWeight();
        float distance2 = pow(p.x - aiball->getPos().x, 2.0) + pow(p.y - aiball->getPos().y, 2.0);
        float distance = sqrt(distance2) - player->getR() - aiball->getR();
        if (distance < 80) {
            // 降低AI灵敏度
            if(CCRANDOM_0_1() < 0.3)
                break;
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
        
        if(CCRANDOM_0_1() < 0.8) {
            Vec2 newDir = player->getPos() - demon->getPos();
            if(newDir.x*newDir.x + newDir.y*newDir.y > maxH*maxH/4) continue;
            newDir.normalize();
            demon->setDirection(newDir);
        }
    }
}

/**
 * 计时器
 */
void Game::gametimer(float delta) {
    --timeCount;
    int minute = timeCount/60;
    int seconds = timeCount%60;
    __String s;
    s.initWithFormat("%02d:%02d",minute,seconds);
    label_time->setString(s._string);
    
    // 游戏结束
    if(timeCount <= 0)
        gameOver();
}

/**
 * 游戏结束
 */
void Game::gameOver() {
    // 停止交互
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    // 游戏结束音效
    // ...
    // 显示游戏结束对话框
    // ...
}

/**
 * 退出场景
 */
void Game::onExit() {
    // 关闭所有回调
    this->unscheduleUpdate();
    this->unscheduleAllCallbacks();
    
    Layer::onExit();
}

/**
 * 析构函数
 */
Game::~Game(){
    // 销毁所有对象
    this->removeAllChildren();
}

#pragma mark -工具函数

/**
 * 游戏变量初始化
 */
void Game::initData() {
    
    // 游戏时间
    timeCount = maxSeconds;
    // baball个数
    baseNum = maxBaseBallNum;
    
    // 默认不缩放
    scale = 1.0f;
    
    // 默认游戏状态
    CurState = IDLE_NORMAL;
    
    // 对象容器初始化
    AIBallArray = Vector<AIBall*>();
    DemonArray = Vector<Demon*>();

    // 边界顶点数组
    int borderX = maxW;
    int borderY = maxH;
    Vertexs[0] = Vec2(borderX, borderY);
    Vertexs[1] = Vec2(borderX, -borderY);
    Vertexs[2] = Vec2(-borderX, -borderY);
    Vertexs[3] = Vec2(-borderX, borderY);
}

/**
 * 添加UI
 */
void Game::addUI() {
    
    uilayer = LayerColor::create(Color4B(255, 255, 255, 0), ScreenWidth, ScreenHeight);
    addChild(uilayer, 100000);
    
    // left
    debuglabel = Label::create();
    debuglabel->setString("0");
    debuglabel->setAnchorPoint(Vec2(0, 1));
    debuglabel->setPosition(Vec2(5,ScreenHeight));
    uilayer->addChild(debuglabel);
    
    label_weight = Label::create();
    label_weight->setString("weight");
    label_weight->setAnchorPoint(Vec2(0, 1));
    label_weight->setPosition(Vec2(5, ScreenHeight - debuglabel->getContentSize().height));
    uilayer->addChild(label_weight);
    
    label_scale = Label::create();
    label_scale->setString("scale");
    label_scale->setAnchorPoint(Vec2(0, 1));
    label_scale->setPosition(Vec2(5, ScreenHeight - label_scale->getContentSize().height*2));
    uilayer->addChild(label_scale);
    
    // center
    label_time = Label::create();
    label_time->setString("00:00");
    label_time->setAnchorPoint(Vec2(0.5, 1));
    label_time->setPosition(ScreenWidth/2, ScreenHeight);
    uilayer->addChild(label_time);
    
    // right
    label_ainum = Label::create();
    label_ainum->setString("ainum");
    label_ainum->setAnchorPoint(Vec2(0, 1));
    label_ainum->setPosition(Vec2(ScreenWidth/3*2,ScreenHeight));
    uilayer->addChild(label_ainum);
    
    label_basenum = Label::create();
    label_basenum->setString("basenum");
    label_basenum->setAnchorPoint(Vec2(0, 1));
    label_basenum->setPosition(Vec2(ScreenWidth/3*2,ScreenHeight - label_basenum->getContentSize().height));
    uilayer->addChild(label_basenum);
    
    label_demon = Label::create();
    label_demon->setString("demon");
    label_demon->setAnchorPoint(Vec2(0, 1));
    label_demon->setPosition(ScreenWidth/3*2,ScreenHeight - label_basenum->getContentSize().height*2);
    uilayer->addChild(label_demon);
    
    // 绘制屏幕中心
    auto centerLabel = Label::create();
    centerLabel->setString("+++++++++++");
    centerLabel->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    uilayer->addChild(centerLabel);
    
    // 背景图片
    auto game_bg = Sprite::create("game_bg.jpg");
    game_bg->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    //gameLayer->addChild(game_bg);
    
    // 按钮菜单
    // 1.返回按钮
    auto item_back = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Game::back, this));
    item_back->setPosition(Vec2(VisiableSize.width - item_back->getContentSize().width/2, VisiableSize.height - item_back->getContentSize().height/2));
    
    // 2.加速按钮
    auto item_dash = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Game::dash, this));
    item_dash->setPosition(Vec2(VisiableSize.width - item_dash->getContentSize().width/2, item_dash->getContentSize().height/2));
    
    // 3.缩放按钮
    auto item_scaleup = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Game::scaleup, this));
    item_scaleup->setPosition(Vec2(item_scaleup->getContentSize().width, item_scaleup->getContentSize().height));
    
    auto item_scaledown = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Game::scaledown, this));
    item_scaledown->setPosition(Vec2(item_scaledown->getContentSize().width, item_scaledown->getContentSize().height*3));
    
    // 按钮菜单
    menu = Menu::create(item_back, item_dash, item_scaleup, item_scaledown, NULL);
    menu->setPosition(Vec2::ZERO);
    uilayer->addChild(menu,1);
    
    // drawnode
    drawNode = DrawNode::create();
    addChild(drawNode);
    
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
    player->setLabel("名字起个啥😁");
    addChild(player);
    AIBallArray.pushBack(player);
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

void Game::createAIBAlls(int num) {
    for (int i = 0 ; i<num ; i++) {
        auto aiball = AIBall::create();
        
        addChild(aiball);
        AIBallArray.pushBack(aiball);
    }
}

void Game::createDemonBalls(int num) {
    for (int i = 0; i < num ; i++) {
        auto demon = Demon::create();
        demon->setLabel("😈恶魔😈");
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
        bool pass = (random > 0.2) ? true : false;
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
    if (DemonArray.size() > 5) return;
    if (random < 0.1) {
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
    
    // 缩放静止的球
    for (int i = 0 ; i < maxBaseBallNum ; i++) {
        staticArray[i].scale(scale);
    }
    
    // 缩放AIBall
    for (Vector<AIBall*>::const_iterator it = AIBallArray.begin(); it != AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        aiball->scale(scale);
    }
    
    // 缩放player
    player->scale(scale);
    
}

# pragma mark -事件函数
/**
 * 返回到菜单
 */
void Game::back(cocos2d::Ref* pSender) {
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene()));
}

/**
 * 加速
 */
void Game::dash(cocos2d::Ref *pSender) {
    player->speedUp();
    DelayTime *delay = DelayTime::create(dashTime);
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(PlayerBall::endSpeedUp, player));
    Sequence *action = Sequence::create(delay,fun, NULL);
    runAction(action);
}

/**
 * 缩放
 */
void Game::scaleup(cocos2d::Ref *pSender) {
    scaleScreen(0.99);
}

void Game::scaledown(cocos2d::Ref *pSender) {
    scaleScreen(1.01);
}

#pragma mark -触屏事件
/**
 * 注册屏幕触摸事件
 */
void Game::addTouchListener() {
    // 开启交互
    //this->setTouchEnabled(true);
    // 定义事件分发
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    // 单点触控
    //this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
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

/**
 * 触摸事件
 */
bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    startPoint = touch->getLocation();
    return true;
}

void Game::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cout<<"moved"<<endl;
}

void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    endPoint = touch->getLocation();
    // 更新玩家移动方向
    Vec2 newDir = endPoint - startPoint;
    
    if (abs(newDir.x) < 0.01f || abs(newDir.y) < 0.01f) {
        newDir = Vec2::ZERO;
        // RUN_NORMAL -> IDLE_NORMAL
        if (CurState == RUN_NORMAL) {
            CurState = IDLE_NORMAL;
        }
        // IDLE_NORMAL -> RUN_NORMAL
        else if (CurState == IDLE_NORMAL) {
            CurState = RUN_NORMAL;
        }
    }
    // IDLE_NORMAL -> RUN_NORMAL
    else if (CurState == IDLE_NORMAL) {
        CurState = RUN_NORMAL;
    }
    
    newDir.normalize();
    player->setDir(newDir);
}

void Game::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cout<<"cancelled"<<endl;
}
