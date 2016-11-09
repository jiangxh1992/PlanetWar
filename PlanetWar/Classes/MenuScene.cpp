//
//  MenuScene.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#include "MenuScene.h"
#include "Game.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

/**
 * 创建菜单场景
 */
Scene* MenuScene::createScene() {
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

/**
 * 菜单初始化
 */
bool MenuScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    // 打印屏幕尺寸
    using namespace std;
    cout<<"screenWidth:"<<ScreenWidth<<endl;
    cout<<"screenHeight:"<<ScreenHeight<<endl;
    
    // 1.开场背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_bg.mp3", true);
    
    // 2.菜单页面背景图片
    auto menu_bg = Sprite::create("menu_bg.png");
    menu_bg->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    
    this->addChild(menu_bg);
    
    // 3.按钮菜单
    // 开始游戏按钮
    auto item_startgame = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MenuScene::startGame, this));
    item_startgame->setPosition(Vec2::ZERO);
    
    // 按钮菜单
    auto menu = Menu::create(item_startgame, NULL);
    menu->setPosition(Vec2(VisiableSize.width/2, VisiableSize.height/2));
    this->addChild(menu,1);
    
    
    return true;
}

/**
 * 跳转到游戏场景
 */
void MenuScene::startGame(cocos2d::Ref* pSender) {
    Director::getInstance()->replaceScene(Game::createScene());
}
