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
    // 随机半径
    radius = 30*CCRANDOM_0_1();
    // 随机颜色
    color = Color4F(100, 40, 80, 1.0);
    
    // 随机图片
    //initWithFile("CloseNormal.png");
    
    // 设置位置
    setPosition(Vec2(x, y));
    
    // 开启安帧更新
    this->scheduleUpdate();
    
    return true;
}

/**
 * 绘图
 */
void BaseBall::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
    ccDrawColor4F(20, 80, 100, color.a);
    ccDrawSolidCircle(Vec2(0, 0), radius, 360, radius*2);

}

/**
 * 安帧更新
 */
void BaseBall::update(float time) {
    x++;
    setPosition(Vec2(x, y));
}
