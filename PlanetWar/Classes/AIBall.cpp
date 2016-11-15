//
//  AIBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 9/11/16.
//
//

#include "AIBall.h"
#include "BaseBall.h"
#include "Game.h"
#include <math.h>
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
    position = Vec2((CCRANDOM_0_1()-0.5) * maxW, (CCRANDOM_0_1()-0.5) * maxH);
    // 初始重量
    updateWeight(minWeight);
    // 随机颜色
    color = Color4F(255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 1.0);
    // 随机方向
    direction = Vec2((CCRANDOM_0_1()*2-1), (CCRANDOM_0_1()*2-1));
    direction.normalize();
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
 * 更新重量
 */
void AIBall::updateWeight(int addedWeight) {
    weight += addedWeight;
    // 速度(>=1)
    speed = sqrt(Energy/weight);
    if (speed<1) speed = 1;
    // 半径
    radius = sqrt(weight*10/PI);
}

/**
 * 安帧更新
 */
void AIBall::update(float time) {
    // 检测吃小球
    for (Vector<BaseBall*>::const_iterator it = Game::sharedGame()->baseBallArray.begin(); it != Game::sharedGame()->baseBallArray.end(); it++) {
        BaseBall *baseball = *it;
        if (!baseball) return;
        double distance = pow(baseball->getPos().x -  position.x, 2) + pow(baseball->getPos().y - position.y, 2);
        if (distance <= radius*radius) {
            // 吃掉baseball，获得其体重
            updateWeight(baseball->getWeight());
            // 移除baseball
            Game::sharedGame()->baseBallArray.eraseObject(baseball);
            Game::sharedGame()->removeChild(baseball);
        }
    }
    
    // 检测吞并
    for (Vector<AIBall*>::const_iterator it = Game::sharedGame()->AIBallArray.begin(); it != Game::sharedGame()->AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        if (!aiball || !aiball->weight) return;
        if (weight > aiball->weight) {
            double distance = pow(aiball->getPos().x -  position.x, 2) + pow(aiball->getPos().y - position.y, 2);
            if (distance <= pow(radius - aiball->radius, 2)) {
                // 吃掉baseball，获得其体重
                updateWeight(aiball->getWeight());
                // 移除baseball
                Game::sharedGame()->AIBallArray.eraseObject(aiball);
                Game::sharedGame()->removeChild(aiball);
            }
        }
    }
    
}

/**
 * 定时器
 */
void AIBall::fixedUpdate(float delta) {
    
    // 1.移动
    position += direction * speed;
    setPosition(position);
    
    // 2.检测边界
    if(position.x >= maxW-radius || position.x <= -(maxW-radius)) {
        position -= direction * speed;
        direction.x = -direction.x;
        direction.y = CCRANDOM_0_1();
        direction.normalize();
    }else if(position.y >= maxH-radius || position.y <= -(maxH-radius)) {
        position -= direction * speed;
        direction.y = -direction.y;
        direction.x = CCRANDOM_0_1();
        direction.normalize();
    }
    
    // 3.简单AI（躲大追小）
//    // 搜索最近的球
//    AIBall *nearestball = *Game::sharedGame()->AIBallArray.begin();
//    if (!nearestball) return;
//    for (Vector<AIBall*>::const_iterator it = Game::sharedGame()->AIBallArray.begin()+1; it != Game::sharedGame()->AIBallArray.end(); it++) {
//        AIBall *nextball = *it;
//        if(!nextball) return;
//        double nearestDis = pow(nearestball->getPos().x-position.x, 2) + pow(nearestball->getPos().y-position.y, 2);
//        double newDis = pow(nextball->getPos().x-position.x, 2) + pow(nextball->getPos().y-position.y, 2);
//        if (newDis < nearestDis) {
//            nearestball = nextball;
//        }
//    }
//    // 躲大追小
//    Vec2 dir = nearestball->position - position;
//    dir.normalize();
//    if (weight > nearestball->weight) {
//        direction = dir;
//    }else {
//        direction = -dir;
//    }

}
