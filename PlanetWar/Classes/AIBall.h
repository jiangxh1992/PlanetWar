//
//  AIBall.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 9/11/16.
//
//

#ifndef __PlanetWar__AIBall__ 
#define __PlanetWar__AIBall__

#include "BaseBall.h"

class AIBall : public BaseBall {

/** 重写函数 **/
public:
    // 创建类对象
    static AIBall* create();
	// 对象初始化
	virtual bool init();

/** 内部变量和函数 **/
protected:
    // 移动方向
    cocos2d::Vec2 direction = cocos2d::Vec2::ZERO;
    // 移动速度
    int speed = 0;
    
    // 定时更新
    void fixedUpdate(float delta);
    
/** 对外接口 **/
public:
    
};

#endif /* defined(__PlanetWar__AIBall__) */
