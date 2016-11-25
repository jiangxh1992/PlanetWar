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
    // 安帧更新
    virtual void update(float time);
    // 析构函数
    virtual ~AIBall();

/** 内部变量和函数 **/
protected:
    // 移动方向
    cocos2d::Vec2 direction = cocos2d::Vec2::ZERO;
    // 移动速度
    int speed = 0;
    
    // 专用更新(禁止子类重用)
    void thisUpdate(float delta);
    // 通用更新(用于子类重用)
    virtual void sharedUpdate(float delta);
    
/** 对外接口 **/
public:
    // 更新重量
    virtual void updateWeight(int addedWeight);
    
};

#endif /* defined(__PlanetWar__AIBall__) */
