//
//  Demon.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 30/11/16.
//
//

#ifndef __PlanetWar__Demon__ 
#define __PlanetWar__Demon__
#include "AIBall.h"
USING_NS_CC;

class Demon : public AIBall {
    int power; // 攻击力
    int life;  // 生命值
public:
    // 绘制图形
    virtual void draw(cocos2d::Renderer*renderer, const cocos2d::Mat4& transform, uint32_t flags);
	// 创建类对象
	static Demon* create();
	// 对象初始化
	virtual bool init();
	// 析构函数
    virtual ~Demon();
    
    // 碰撞检测重写
    virtual void sharedUpdate(float delta);
    virtual void updateWeight(int addedWeight);
};

#endif /* defined(__PlanetWar__Demon__) */
