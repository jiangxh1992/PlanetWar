//
//  AIBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 9/11/16.
//
//

#include "AIBall.h"
#include "StaticBall.h"
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
    
    commenInit();
    
    // 开启安帧更新
    this->scheduleUpdate();
    // 开启定时器
    this->schedule(schedule_selector(AIBall::thisUpdate), Interval);
    
    return true;
}

void AIBall::commenInit() {
    eatAINum = 0;
    eatBaseNum = 0;
    // label
    label_tag = Label::create();
    label_tag->setString("😜智多星☺️");
    label_tag->setPosition(Vec2(0, radius+label_tag->getContentSize().height));
    addChild(label_tag);
    // 步长
    speed = maxSpeed;
    // 随机位置
    position = Vec2((CCRANDOM_0_1()-0.5) * maxW, (CCRANDOM_0_1()-0.5) * maxH);
    // 初始重量
    updateWeight(minWeight);
    // 随机颜色
    color = Color4F(10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 1.0);
    // 随机方向
    direction = Vec2((CCRANDOM_0_1()*2-1), (CCRANDOM_0_1()*2-1));
    direction.normalize();
    
    // 移动间隔帧数
    speedInterval = 1.0f;
    // 间隔帧数计数器
    intervalCount = 0.9f;
    // 设置位置
    setPosition(position);
    // drawnode
    drawNode = DrawNode::create();
    this->addChild(drawNode);
}

/**
 * 更新重量
 */
void AIBall::updateWeight(int addedWeight) {
    weight += addedWeight;
    // 半径
    radius = sqrt(weight*Game::sharedGame()->scale);
    
    label_tag->setPosition(Vec2(0, radius+label_tag->getContentSize().height));
}

/**
 * 安帧更新
 */
void AIBall::update(float time) {
    sharedUpdate(time);
}

/**
 * 本类专用更新
 */
void AIBall::thisUpdate(float delta) {
    
    // 0.延迟检测
    speedInterval = 1+(double)weight/(double)minWeight/20;
    if (intervalCount < speedInterval) {
        intervalCount += 0.2*Game::sharedGame()->scale;
        return;
    }else {
        intervalCount = 1.0;
    }
    
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

}

/**
 * 碰撞检测
 */
void AIBall::sharedUpdate(float delta) {
    
    // 1.检测吃小球
    for (int i = 0; i < maxBaseBallNum ; i++) {
        StaticBall baseball = Game::sharedGame()->staticArray[i];
        if (!baseball.isActive) continue;
        double distance = pow(baseball.position.x -  position.x, 2) + pow(baseball.position.y - position.y, 2);
        if (distance <= radius*radius) {
            // 吃掉baseball，获得其体重
            updateWeight(baseball.weight);
            eatBaseNum++;
            // 移除baseball
            Game::sharedGame()->staticArray[i].isActive = false;
            Game::sharedGame()->baseNum --;
        }
    }

    // 2.检测吞并
    Vector<AIBall*> autoreleasepool = Vector<AIBall*>();
    for (Vector<AIBall*>::const_iterator it = Game::sharedGame()->AIBallArray.begin(); it != Game::sharedGame()->AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        if (weight > aiball->getBallWeight()) {
            double distance = pow(aiball->getPos().x -  position.x, 2) + pow(aiball->getPos().y - position.y, 2);
            if (distance <= pow(radius - aiball->radius, 2)) {
                // 获得其体重
                updateWeight(aiball->getBallWeight());
                eatAINum++;
                autoreleasepool.pushBack(aiball);
            }
        }
    }
    // 移除回收池内的死球
    for (Vector<AIBall*>::const_iterator it = autoreleasepool.begin(); it != autoreleasepool.end(); it++) {
        AIBall *ball = *it;
        // 移除
        Game::sharedGame()->AIBallArray.eraseObject(ball);
        Game::sharedGame()->removeChild(ball);
    }
}

/**
 * 缩放
 */
void AIBall::scale(float scale) {
    // postion
    position *= scale;
    // speed
    speedInterval /= scale;
    // radius
    updateWeight(0);
}

void AIBall::setLabel(__String label) {
    label_tag->setString(label._string);
}

/**
 * 析构函数
 */
AIBall::~AIBall() {
    this->unscheduleUpdate();
    this->unscheduleAllCallbacks();
}
