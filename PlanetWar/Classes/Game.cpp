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

/**
 * 游戏初始化
 */
bool Game::init() {

    if (!Layer::init()) {
        return false;
    }
    
    // 添加UI
    addUI();
    
    // 静态baseball
    for (int i = 0; i<100; i++) {
        auto ball = BaseBall::create();
        this->addChild(ball);
    }
    
    // 动态AIBall
    for (int i = 0 ; i<5 ; i++) {
        auto aiball = AIBall::create();
        this->addChild(aiball);
    }
    
    return true;
}

/**
 * 添加UI
 */
void Game::addUI() {
    // 背景图片
    auto game_bg = Sprite::create("game_bg.jpg");
    game_bg->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    this->addChild(game_bg);
    
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
 * 返回到菜单
 */
void Game::back(cocos2d::Ref* pSender) {
    Director::getInstance()->replaceScene(MenuScene::createScene());
}
