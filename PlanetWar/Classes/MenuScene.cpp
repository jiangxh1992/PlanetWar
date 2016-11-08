//
//  MenuScene.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#include "MenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MenuScene::createScene() {
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

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
    auto menu_bg = Sprite::create("HelloWorld.png");
    menu_bg->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    
    this->addChild(menu_bg);
    
    return true;
}
