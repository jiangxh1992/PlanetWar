//
//  AIBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 9/11/16.
//
//

#include "AIBall.h"
USING_NS_CC;

/**
 * 创建对象
 */
AIBall* AIBall::create() {
    AIBall *sprite = new AIBall();
    
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

/**
 * 初始化
 */
bool AIBall::init() {
    if (!Sprite::init()) {
        return false;
    }
    // 随机位置
    position = Vec2(CCRANDOM_0_1() * maxW, CCRANDOM_0_1() * maxH);
    // 随机半径
    radius = CCRANDOM_0_1()*20;
    // 随机颜色
    color = Color4F(255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 1.0);
    // 随机方向
    direction = Vec2((CCRANDOM_0_1()*2-1), (CCRANDOM_0_1()*2-1));
    // 随机图片
    //initWithFile("CloseNormal.png");
    
    // 设置位置
    setPosition(position);
    // drawnode
    drawNode = DrawNode::create();
    this->addChild(drawNode);
    
    // 开启安帧更新
    //this->scheduleUpdate();
    // 开启定时器
    this->schedule(schedule_selector(AIBall::fixedUpdate), Interval);
    
    return true;
}

/**
 * 定时器
 */
void AIBall::fixedUpdate(float delta) {
    position += direction;
    setPosition(position);
}
