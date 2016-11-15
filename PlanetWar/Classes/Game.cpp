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
USING_NS_CC;

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
    createAIBAlls();
    
    // 创建玩家
    player = PlayerBall::create();
    this->addChild(player);
    AIBallArray.pushBack(player);
    
    // 开启玩家触屏交互
    addTouchListener();
    
    // 开启定时器
    this->schedule(schedule_selector(Game::createBaseBallTimer), Interval*50);
    
    // 开启观察者
    this->schedule(schedule_selector(Game::gameObserver), Interval);
    
    return true;
}

/**
 * 游戏变量初始化
 */
void Game::initData() {
    baseBallArray = Vector<BaseBall*>();
    //AIBallArray = __Array::create();
}

/**
 * 添加UI
 */
void Game::addUI() {
    // 背景图片
    auto game_bg = Sprite::create("game_bg.jpg");
    game_bg->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    //this->addChild(game_bg);
    
    // 按钮菜单
    // 返回按钮
    auto item_back = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Game::back, this));
    item_back->setPosition(Vec2(VisiableSize.width - item_back->getContentSize().width/2, VisiableSize.height - item_back->getContentSize().height/2));
    
    // 按钮菜单
    auto menu = Menu::create(item_back, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,1);
    
}

/**
 * BaseBall工厂函数
 */
void Game::createBaseBalls(int num) {
    for (int i = 0; i<num; i++) {
        auto ball = BaseBall::create();
        this->addChild(ball);
        baseBallArray.pushBack(ball);
    }
}

/**
 * AIBall工厂函数
 */
void Game::createAIBAlls() {
    for (int i = 0 ; i<20 ; i++) {
        auto aiball = AIBall::create();
        this->addChild(aiball);
        AIBallArray.pushBack(aiball);
    }
}

/**
 * 定时生成小球
 */
void Game::createBaseBallTimer(float delta) {
    if (baseBallArray.size() > maxBaseBallNum) return;
    createBaseBalls(200*CCRANDOM_0_1());
}

/**
 * 返回到菜单
 */
void Game::back(cocos2d::Ref* pSender) {
    Director::getInstance()->replaceScene(MenuScene::createScene());
}

/**
 * 注册屏幕触摸事件
 */
void Game::addTouchListener() {
    // 开启交互
    this->setTouchEnabled(true);
    // 定义事件分发
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    // 单点触控
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
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
    newDir.normalize();
    player->setDir(newDir);
    
}

/**
 * 游戏观察者
 */
void Game::gameObserver(float delta) {
    // 死亡球回收池
    Vector<BaseBall*> deadballs = Vector<BaseBall*>();
    // 检测吃小球
    for (Vector<AIBall*>::const_iterator it = AIBallArray.begin(); it != AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        for (Vector<BaseBall*>::const_iterator it2 = baseBallArray.begin(); it2 != baseBallArray.end(); it2++) {
            BaseBall *baseball = *it2;
            
            double distance = pow(baseball->getPos().x - aiball->getPos().x, 2) + pow(baseball->getPos().y - aiball->getPos().y, 2);
            if (distance <= pow(aiball->getR(), 2)) {
                // 吃掉baseball，获得其体重
                aiball->updateWeight(baseball->getWeight());
                // 移除baseball
                baseBallArray.eraseObject(baseball);
                // 添加到待回收池
                deadballs.pushBack(baseball);
            }
        }
    }
    
    // 移除回收池内的死球
    for (Vector<BaseBall*>::const_iterator it = deadballs.begin(); it != deadballs.end(); it++) {
        removeChild(*it);
    }
}
