//
//  PlayerBall.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 14/11/16.
//
//

#ifndef __PlanetWar__PlayerBall__ 
#define __PlanetWar__PlayerBall__
#include "AIBall.h"

class PlayerBall : public AIBall {
    
/** 重写函数 **/
public:
	// 创建类对象
	static PlayerBall* create();
	// 对象初始化
	virtual bool init();
    // 安帧更新
    virtual void update(float time);
    // 缩放
    virtual void scale(float scale);
    // 析构函数
    virtual ~PlayerBall();

/** 内部变量和函数 **/
protected:
    
    // 专用更新
    void thisUpdate(float delta);
    
/** 对外接口 **/
public:
    void setDir(const cocos2d::Vec2 newDir) {direction = newDir;};
	
};

#endif /* defined(__PlanetWar__PlayerBall__) */
