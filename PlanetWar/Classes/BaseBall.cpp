//
//  BaseBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#include "BaseBall.h"
USING_NS_CC;

/**
 * 创建对象
 */
BaseBall* BaseBall::create() {
	BaseBall *sprite = new BaseBall();
	if (sprite && sprite->init())
	{
        sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

/**
 * 游戏初始化
 */
bool BaseBall::init() {
    // 随机位置
    x = CCRANDOM_0_1() * maxW;
    y = CCRANDOM_0_1() * maxH;
    
    // 随机图片
    initWithFile("CloseNormal.png");
    
    // 设置位置
    setPosition(Vec2(x, y));
    
    return true;
}
