//
//  Game.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#ifndef __PlanetWar__Game__ 
#define __PlanetWar__Game__
#include "PlayerBall.h"

class Game : public cocos2d::Layer {
  
/** 重写函数 **/
public:
	// 创建类对象
	static cocos2d::Scene* createScene();
	// 对象初始化
	virtual bool init();
    CREATE_FUNC(Game);
    
/** 内部变量和函数 **/
private:
    // 玩家
    PlayerBall *player;
    // 触摸起始点和结束点
    cocos2d::Vec2 startPoint = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 endPoint = cocos2d::Vec2::ZERO;
    
    // 游戏变量初始化
    void initData();
    // 添加UI
    void addUI();
    // BaseBall工厂函数
    void createBaseBalls(int num);
    // AIBall工厂函数
    void createAIBAlls();
    // 定时生成小球
    void createBaseBallTimer(float delta);
    // 返回到菜单页面
    void back(cocos2d::Ref* pSender);
    // 注册屏幕触摸事件
    void addTouchListener();
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    // 游戏观察者（检测吞并情况）
    void gameObserver(float delta);

/** 对外接口 **/
public:
    // 游戏场景单例
    static Game* sharedGame();
    // 数组
    // BaseBall数组
    cocos2d::Vector<BaseBall*> baseBallArray;
    // AIBall数组
    cocos2d::Vector<AIBall*> AIBallArray;

    //cocos2d::__Array* getBaseBallArray() {return baseBallArray;};
    //cocos2d::__Array* getAIBallArray() {return AIBallArray;};

};

#endif /* defined(__PlanetWar__Game__) */
