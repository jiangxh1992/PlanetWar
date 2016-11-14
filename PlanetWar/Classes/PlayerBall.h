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
    // 定时更新
    virtual void fixedUpdate(float delta);

/** 内部变量和函数 **/
protected:
    
/** 对外接口 **/
public:

	
};

#endif /* defined(__PlanetWar__PlayerBall__) */
