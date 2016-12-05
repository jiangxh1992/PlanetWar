//
//  PlayerBall.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 14/11/16.
//
//  玩家可以控制的球

#ifndef __PlanetWar__PlayerBall__ 
#define __PlanetWar__PlayerBall__
#include "AIBall.h"
USING_NS_CC;

class PlayerBall : public AIBall {
/** 重写函数 **/
public:
	static PlayerBall* create();
	virtual bool init();
    // 安帧更新
    virtual void update(float time);
    // 析构函数
    virtual ~PlayerBall();

/** 内部变量和函数 **/
protected:
    
    bool isSpeedUp = false;      // 加速开关
    int speedUpCount = 0;        // 加速计时器
    bool isActive = true;        // 是否活跃
    bool switchBlink = false;    // 闪烁开关
    
    virtual void thisUpdate(float delta);
    virtual void sharedUpdate(float delta);
    
/** 对外接口 **/
public:
    void speedUp();
    void startProtectPlayer(); // 无敌状态
    void endProtectPlayer();
    
    void setDir(const cocos2d::Vec2 newDir) {direction = newDir;};
    void setIsActive(bool active){isActive = active;}
    
    bool getIsActive(){return isActive;}
    
};

#endif /* defined(__PlanetWar__PlayerBall__) */
