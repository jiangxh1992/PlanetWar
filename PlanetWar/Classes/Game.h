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
    
    // 添加UI
    void addUI();
    // 返回到菜单页面
    void back(cocos2d::Ref* pSender);
    // 注册屏幕触摸事件
    void addTouchListener();
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

/** 对外接口 **/
public:
    // 游戏场景单例
    Game* sharedGame();

};

#endif /* defined(__PlanetWar__Game__) */
