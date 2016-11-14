//
//  PlayerBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 14/11/16.
//
//

#include "PlayerBall.h"
USING_NS_CC;

PlayerBall* PlayerBall::create() {
	PlayerBall *sprite = new PlayerBall();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool PlayerBall::init() {
    if (!Sprite::init()) {
        return false;
    }
    // 位置初始化在屏幕中心
    position = Vec2(VisiableSize.width/2, VisiableSize.height/2);
    
    // 初始重量
    weight = minWeight*2;
    // 速度(>=1)
    speed = sqrt(Energy/weight);
    // 半径
    radius = sqrt(weight*5/PI);
    
    // 随机颜色
    color = Color4F(255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 1.0);
    // 随机图片
    // initWithFile("CloseNormal.png");
    // isDraw = false;
    
    // 设置位置
    setPosition(position);
    // drawnode
    drawNode = DrawNode::create();
    this->addChild(drawNode);
    
    // 开启安帧更新
    this->scheduleUpdate();
    // 开启定时器
    this->schedule(schedule_selector(PlayerBall::fixedUpdate), Interval);
    
    return true;
}

/**
 * 定时更新
 */
void PlayerBall::fixedUpdate(float delta) {
    // 移动
    position += direction*speed;
    setPosition(position);
    
    // 检测边界
    if(position.x >= VisiableSize.width-radius || position.x <= radius || position.y >= VisiableSize.height-radius || position.y <= radius) {
        position -= direction*speed;
        setPosition(position);
    }
}
