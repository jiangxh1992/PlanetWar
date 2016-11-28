//
//  Game.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#include "Game.h"
#include "BaseBall.h"
#include "AIBall.h"
#include "MenuScene.h"
#include <math.h>


/**
 * 创建游戏场景
 */
Scene* Game::createScene() {
    auto scene = Scene::create();
    auto layer = Game::create();
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
    
    // 静态baseball
    createBaseBalls(maxBaseBallNum);
    // 动态AIBall
    createAIBAlls(maxAIBallNum);
    
    // 创建玩家
    player = PlayerBall::create();
    addChild(player);
    AIBallArray.pushBack(player);
    
    // 开启玩家触屏交互
    addTouchListener();
    
    // 开启定时器
    this->schedule(schedule_selector(Game::createBaseBallTimer), Interval*30);
    
    // 开启观察者
    this->schedule(schedule_selector(Game::gameObserver), Interval);
    
    return true;
}

/**
 * 游戏变量初始化
 */
void Game::initData() {
    
    // 默认游戏状态
    CurState = IDLE_NORMAL;
    
    // 对象容器初始化
    AIBallArray = Vector<AIBall*>();

    // 3,4,5边形
//    polyData = new Point*[3];
//    for (int i = 3; i<=5; i++) {
//        polyData[i-3] = new Point[i];
//        for (int j = 0 ; j<i; j++) {
//            polyData[i-3][j] = Vec2(cos(2*PI*j/i), sin(2*PI*j/i));
//        }
//    }
}

/**
 * 添加UI
 */
void Game::addUI() {
    
    uilayer = LayerColor::create(Color4B(255, 255, 255, 1.0), ScreenWidth, ScreenHeight);
    addChild(uilayer);
    
    // debug text
    debuglabel = Label::create();
    debuglabel->setString("TEST!!!");
    debuglabel->setBMFontSize(100);
    debuglabel->setPosition(Vec2(ScreenWidth/2,ScreenHeight/2));
    uilayer->addChild(debuglabel,100);
    
    
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
    
    // 按钮菜单
    menu = Menu::create(item_back, item_dash, NULL);
    menu->setPosition(Vec2::ZERO);
    uilayer->addChild(menu,1);
    
    // drawnode
    drawNode = DrawNode::create();
    addChild(drawNode);
    
}

/**
 * BaseBall工厂函数
 */
void Game::createBaseBalls(int num) {
    staticArray = new StaticBall[num];
    for (int i = 0; i<num; i++) {
        staticArray[i] = StaticBall();
    }
}

/**
 * AIBall工厂函数
 */
void Game::createAIBAlls(int num) {
    for (int i = 0 ; i<num ; i++) {
        auto aiball = AIBall::create();
        addChild(aiball);
        AIBallArray.pushBack(aiball);
    }
}

/**
 * 定时生成小球和AIBall
 */
void Game::createBaseBallTimer(float delta) {
    // 小球随机激活
    for (int i = 0; i<maxBaseBallNum; i++) {
        bool random = CCRANDOM_0_1()>0.5 ? true : false;
        if (random && !staticArray[i].isActive) {
            staticArray[i].reActive();
        }
    }
    // AIBall
//    int createNum = maxAIBallNum - (int)AIBallArray.size();
//    if (createNum > 0) {
//        createAIBAlls(createNum);
//    }
}

/**
 * 图形绘制
 */
void Game::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
    // 清空之前的绘制
    drawNode->clear();
    // 生成随机边数
    //int polyNum = 2 + CCRANDOM_0_1()*3;
    
    for (int i = 0 ; i < maxBaseBallNum ; i++) {
        if (!staticArray[i].isActive) continue;
        // 绘制多边形
//        Point *vertexs = new Point[polyNum];
//        for (int i = 0; i<polyNum; i++) {
//            vertexs[i].x = staticArray[i].position.x + staticArray[i].radius * polyData[polyNum-3][i].x;
//            vertexs[i].y = staticArray[i].position.y + staticArray[i].radius * polyData[polyNum-3][i].y;
//        }
        //drawNode->drawPoly(vertexs, polyNum, true, staticArray[i].color);
        drawNode->drawDot(staticArray[i].position, staticArray[i].radius, staticArray[i].color);
        // 深度
        drawNode->setGlobalZOrder(-1);
    }
}

/**
 * 屏幕缩放
 */
void Game::scaleScreen(float scale) {
    maxW *= scale;
    maxH *= scale;
    
    // baseball缩放
    for (int i = 0; i < maxBaseBallNum ; i++) {
        StaticBall baseball = Game::sharedGame()->staticArray[i];
        if (!baseball.isActive) continue;
        // size
        baseball.radius *= scale;
        // position
        baseball.position *= scale;
    }
    
    // AIBall缩放
    for (Vector<AIBall*>::const_iterator it = Game::sharedGame()->AIBallArray.begin(); it != Game::sharedGame()->AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        // size
        aiball->scaleRadius(scale);
        // position
        aiball->scalePosition(scale);
        // speed
        aiball->scaleSpeed(scale);
    }
    
    // 场景缩放
    setPosition(getPosition()*scale);
    uilayer->setPosition(uilayer->getPosition()*scale);
    
}

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
    scaleScreen(0.5);
}

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
    //oneTouch->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved,this);
    // 触摸结束
    oneTouch->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded,this);
    // 触摸取消
    //oneTouch->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled,this);
    
    eventDispatcher->addEventListenerWithSceneGraphPriority(oneTouch,this);

}

/**
 * 触摸开始事件
 */
bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    startPoint = touch->getLocation();
    return true;
}

/**
 * 触摸结束事件
 */
void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    endPoint = touch->getLocation();
    // 更新玩家移动方向
    Vec2 newDir = endPoint - startPoint;
    
    // RUN_NORMAL -> IDLE_NORMAL
    if (newDir.isZero() && CurState == RUN_NORMAL) {
        CurState = IDLE_NORMAL;
    }
    // IDLE_NORMAL -> RUN_NORMAL
    else if (CurState == IDLE_NORMAL) {
        CurState = RUN_NORMAL;
    }
    
    newDir.normalize();
    player->setDir(newDir);
    
}

// 安帧更新
void Game::update(float time) {
}

/**
 * 游戏观察者
 */
void Game::gameObserver(float delta) {
    //std::cout<<CurState<<std::endl;
//    // 死亡球回收池
//    Vector<BaseBall*> deadballs = Vector<BaseBall*>();
//    // 检测吃小球
//    for (Vector<AIBall*>::const_iterator it = AIBallArray.begin(); it != AIBallArray.end(); it++) {
//        AIBall *aiball = *it;
//        for (Vector<BaseBall*>::const_iterator it2 = baseBallArray.begin(); it2 != baseBallArray.end(); it2++) {
//            BaseBall *baseball = *it2;
//            double distance = pow(baseball->getPos().x - aiball->getPos().x, 2) + pow(baseball->getPos().y - aiball->getPos().y, 2);
//            if (distance <= pow(aiball->getR(), 2)) {
//                // 吃掉baseball，获得其体重
//                aiball->updateWeight(baseball->getWeight());
//                // 移除baseball
//                baseBallArray.eraseObject(baseball);
//                // 添加到待回收池
//                deadballs.pushBack(baseball);
//            }
//        }
//    }
//    
//    // 移除回收池内的死球
//    for (Vector<BaseBall*>::const_iterator it = deadballs.begin(); it != deadballs.end(); it++) {
//        removeChild(*it);
//    }
}

/**
 * 退出场景
 */
void Game::onExit() {
    // 关闭所有回调
    this->unscheduleUpdate();
    this->unscheduleAllCallbacks();
    // 关闭交互监听
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    Layer::onExit();
}

/**
 * 析构函数
 */
Game::~Game(){
    // 销毁所有对象
    this->removeAllChildren();
}
