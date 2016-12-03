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

//转换成string类型
template<typename T>
string Convert2String(const T &value)
{
    stringstream ss;
    ss << value;
    return ss.str();
}

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
    
    // 开场背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music_menu_bg.mp3", true);
    
    addUI();
    
    this->scheduleUpdate();
    
    return true;
}

void MenuScene::update(float time) {
    scaleCount += 0.02;
    menu_bg->setScale(1-sin(scaleCount)*0.4);// 背景缩放
    item_startgame1->setScale(1-sin(scaleCount)*0.1);
    item_startgame2->setScale(1-sin(scaleCount)*0.1);
    item_history->setScale(1-sin(scaleCount)*0.2);
}

/**
 * 场景退出
 */
void MenuScene::onExit() {
    this->removeAllChildren();
    Layer::onExit();
}

#pragma mark- 工具函数
void MenuScene::addUI() {
    
    // 菜单页面背景图片
    menu_bg = Sprite::create("menu_bg.jpg");
    menu_bg->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    addChild(menu_bg);
    
    // 游戏标题
    label_title = Sprite::create("game_title.png");
    label_title->setAnchorPoint(Vec2(0.5, 1));
    label_title->setPosition(Vec2(ScreenWidth/2, ScreenHeight-10));
    addChild(label_title);
    
    // 粒子
    ParticleSystemQuad *particle = ParticleSystemQuad::create("particle_galaxy.plist");
    particle->setPosition(ScreenWidth/2,ScreenHeight/2-20);
    addChild(particle, 10);
    
    // 云层
    auto menu_cloud = Sprite::create("menu_cloud.png");
    menu_cloud->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    addChild(menu_cloud, 20);
    
    // 开始游戏按钮
    item_startgame1 = MenuItemImage::create("btn_gametimer_normal.png", "btn_gametimer_pressed.png", CC_CALLBACK_1(MenuScene::startGameTimer, this));
    item_startgame1->setAnchorPoint(Vec2(1, 0.5));
    item_startgame1->setPosition(Vec2(-15, -20));
    
    item_startgame2 = MenuItemImage::create("btn_gameunlimited_normal.png", "btn_gameunlimited_pressed.png", CC_CALLBACK_1(MenuScene::startGameUnlimited, this));
    item_startgame2->setAnchorPoint(Vec2(0, 0.5));
    item_startgame2->setPosition(Vec2(15, -20));
    
    // 历史记录按钮
    item_history = MenuItemImage::create("btn_history_normal.png","btn_history_pressed.png", CC_CALLBACK_1(MenuScene::openHistory, this));
    item_history->setPosition(Vec2(0, -ScreenHeight/3));
    // 按钮菜单
    auto menu = Menu::create(item_startgame1, item_startgame2, item_history, NULL);
    menu->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    addChild(menu,100);
    
    // 添加历史记录UI
    addHistoryUI();
}

void MenuScene::addHistoryUI() {
    // 游戏数据提取
    string name = "名字起个啥😄";     // 名字
    int new_weight = 500;         // 体重
    int new_demon = 30;                             // 杀死demon数量
    int new_base = 599;           // 吞并baseball数量
    int new_ai =  43;              // 吞并AIBall数量
    
    // 对话框层
    history_layer_bg = LayerColor::create(Color4B(0, 0, 0, 200), ScreenWidth, ScreenHeight);
    history_layer_bg->setPosition(Vec2(0, 0));
    addChild(history_layer_bg, 101);
    Node *history_layer = Node::create();
    history_layer->setPosition(Vec2(ScreenWidth/2, ScreenHeight/2));
    history_layer_bg->addChild(history_layer, 101);
    
    // 默认隐藏历史记录对话框
    history_layer_bg->setVisible(false);
    
    // 对话框背景
    Sprite *dialog_box = Sprite::create("dialog_box.png");
    dialog_box->setAnchorPoint(Vec2(0.5, 0.5));
    dialog_box->setPosition(Vec2(0, 0));
    history_layer->addChild(dialog_box,101);
    
    // 卡通人物
    Sprite *character = Sprite::create("character_win.png");
    character->setAnchorPoint(Vec2(1, 0.5));
    character->setPosition(Vec2(-100, 50));
    history_layer->addChild(character,101);
    
    // 内容背景
    int contentW = ScreenWidth/2-20;
    int contentH = ScreenHeight/2-20;
    int marginTop = 40;
    int marginLeft = 30;
    LayerColor *content_layer = LayerColor::create(Color4B(255, 255, 255, 100), contentW, contentH);
    content_layer->setIgnoreAnchorPointForPosition(false);
    content_layer->setAnchorPoint(Vec2(0, 0.5));
    content_layer->setPosition(Vec2(-80, 20));
    history_layer->addChild(content_layer,101);
    
    Label *gameover = Label::create();
    gameover->setString("WINNER!");
    gameover->setSystemFontName(FontPlanet);
    gameover->setSystemFontSize(15);
    gameover->setAnchorPoint(Vec2(0.5, 1));
    gameover->setPosition(contentW/2, contentH-5);
    content_layer->addChild(gameover,101);
    
    Label *label_name = Label::create();
    label_name->setString("Name:"+name);
    label_name->setSystemFontName(FontPlanet);
    label_name->setAnchorPoint(Vec2(0, 1));
    label_name->setPosition(marginLeft, contentH-marginTop);
    content_layer->addChild(label_name,101);
    
    int labelH = label_name->getContentSize().height+3;
    
    Label *label_weight = Label::create();
    label_weight->setString("Weight:"+Convert2String(new_weight));
    label_weight->setSystemFontName(FontPlanet);
    label_weight->setAnchorPoint(Vec2(0, 1));
    label_weight->setPosition(marginLeft, contentH-marginTop-labelH);
    content_layer->addChild(label_weight,101);
    Label *label_demon = Label::create();
    label_demon->setString("Kill Demon:"+Convert2String(new_demon));
    label_demon->setSystemFontName(FontPlanet);
    label_demon->setAnchorPoint(Vec2(0, 1));
    label_demon->setPosition(marginLeft, contentH-marginTop-labelH*2);
    content_layer->addChild(label_demon,101);
    Label *label_base = Label::create();
    label_base->setString("Eat BaseBall:"+Convert2String(new_base));
    label_base->setSystemFontName(FontPlanet);
    label_base->setAnchorPoint(Vec2(0, 1));
    label_base->setPosition(marginLeft, contentH-marginTop-labelH*3);
    content_layer->addChild(label_base,101);
    Label *label_ai = Label::create();
    label_ai->setString("Eat AIBall:"+Convert2String(new_ai));
    label_ai->setSystemFontName(FontPlanet);
    label_ai->setAnchorPoint(Vec2(0, 1));
    label_ai->setPosition(marginLeft, contentH-marginTop-labelH*4);
    content_layer->addChild(label_ai,101);
    
    // 按钮
    auto item_limited = MenuItemImage::create("btn_limited_normal.png", "btn_limited_pressed.png", CC_CALLBACK_1(MenuScene::showLimitedRecord, this));
    item_limited->setPosition(Vec2(0, 0));
    auto item_unlimited = MenuItemImage::create("btn_unlimited_normal.png", "btn_pressed_normal.png", CC_CALLBACK_1(MenuScene::showUnLimitedRecord, this));
    item_unlimited->setPosition(Vec2(130, 0));
    
    auto item_back = MenuItemImage::create("btn_back_normal.png", "btn_back_pressed.png", CC_CALLBACK_1(MenuScene::hideHistory, this));
    item_back->setPosition(Vec2(-150, -10));
    
    // 按钮菜单
    auto menu = Menu::create(item_limited, item_unlimited, item_back, NULL);
    menu->setPosition(Vec2(0, -80));
    history_layer->addChild(menu,101);
}

#pragma mark- 事件函数
/**
 * 跳转到游戏场景
 */
void MenuScene::startGameTimer(cocos2d::Ref* pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_click.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, Game::createScene(GAME_TIMER)));
}
void MenuScene::startGameUnlimited(cocos2d::Ref *pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_click.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, Game::createScene(GAME_UNLIMITED)));
}

/**
 * 历史记录
 */
void MenuScene::openHistory(cocos2d::Ref *pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_click.mp3");
    history_layer_bg->setVisible(true);
}

void MenuScene::showLimitedRecord(cocos2d::Ref *pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_click.mp3");
}
void MenuScene::showUnLimitedRecord(cocos2d::Ref *pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_click.mp3");
}
void MenuScene::hideHistory(cocos2d::Ref *pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_click.mp3");
    history_layer_bg->setVisible(false);
}
