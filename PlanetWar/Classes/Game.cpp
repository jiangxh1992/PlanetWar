//
//  Game.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#include "Game.h"
#include "BaseBall.h"
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
    
    // 背景图片
    auto game_bg = Sprite::create("game_bg.png");
    game_bg->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    this->addChild(game_bg);
    
    for (int i = 0; i<40; i++) {
        auto ball = BaseBall::create();
        this->addChild(ball);
    }
    
    return true;
}
