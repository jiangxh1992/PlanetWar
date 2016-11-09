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
    
    for (int i; i<30; i++) {
        auto ball = BaseBall::create();
        this->addChild(ball);
    }
    
    return true;
}
