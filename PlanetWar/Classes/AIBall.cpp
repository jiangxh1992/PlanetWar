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
    speed = maxSpeed; // 步长
    position = Vec2((CCRANDOM_0_1()-0.5) * maxW, (CCRANDOM_0_1()-0.5) * maxH);// 随机位置
    
    // 随机颜色
    int index = (colorNum-1)*CCRANDOM_0_1();
    color = Game::sharedGame()->ColorArray[index];
    //color = Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1);
    
    // 随机方向
    direction = Vec2((CCRANDOM_0_1()*2-1), (CCRANDOM_0_1()*2-1));
    direction.normalize();
    
    weight = minWeight;       // 初始重量
    radius = sqrt(weight);    // 半径
    speedInterval = 1.0f;     // 移动间隔帧数
    intervalCount = 0.9f;     // 间隔帧数计数器
    setPosition(position);    // 设置位置
    
    // label
    label_tag = Label::create();
    label_tag->setString("😜智多星☺️");
    label_tag->setPosition(Vec2(0, radius+label_tag->getContentSize().height));
    addChild(label_tag);
    // drawnode
    drawNode = DrawNode::create();
    this->addChild(drawNode);
}

/**
 * 绘图
 */
void AIBall::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
    // 清空之前的绘制
    drawNode->clear();
    //启用混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    if (isDraw) {
        // 绘制实心圆形
        drawNode->drawDot(Vec2(0, 0), radius, color);
        drawNode->drawDot(Vec2(0, 0), radius*0.9, Color4F(1.0, 1.0, 1.0, 0.2));
        drawNode->drawCircle(Vec2(0, 0), radius, 360, radius, false, Color4F(color.r, color.g, color.b, 0.5));
        // 根据球的半径更新当前球的绘制深度，半径越大的绘制在前面覆盖更小的球
        //drawNode->setGlobalZOrder(radius);
        drawNode->setLocalZOrder(radius);
    }
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
    position += direction * speed *speedFactor;
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
    if(Game::sharedGame()->isGameOver) return;
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

    // 回收池
    Vector<AIBall*> autoreleasepool = Vector<AIBall*>();
    // 2.检测AIBall互相吞并
    for (Vector<AIBall*>::const_iterator it = Game::sharedGame()->AIBallArray.begin(); it != Game::sharedGame()->AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        if (weight == aiball->getBallWeight()) continue; // 排除和自身吞并
        // 距离的平方
        double distance2 = pow(aiball->getPos().x -  position.x, 2) + pow(aiball->getPos().y - position.y, 2);
        if(distance2 >= pow(radius - aiball->radius, 2)*1.2) continue; // 还没有吞并
            if (weight > aiball->getBallWeight()) {
                // 当前AIBall吞并对方
                updateWeight(aiball->getBallWeight());
                eatAINum++;
                autoreleasepool.pushBack(aiball);
            }else {
                // 对方吞并当前AIBall
                aiball->updateWeight(weight);
                aiball->eatAINum++;
                autoreleasepool.pushBack(this);
            }
    }
    // 移除回收池内的死球
    for (Vector<AIBall*>::const_iterator it = autoreleasepool.begin(); it != autoreleasepool.end(); it++) {
        AIBall *ball = *it;
        // 移除
        Game::sharedGame()->AIBallArray.eraseObject(ball);
        Game::sharedGame()->removeChild(ball);
    }
    
    // 3.检测与player的吞并
    if(!Game::sharedGame()->getPlayer()->isVisible()) return;
    // AIBall与player的距离的平方
    double D2 = pow(Game::sharedGame()->getPlayer()->getPos().x -  position.x, 2) + pow(Game::sharedGame()->getPlayer()->getPos().y - position.y, 2);
    if(D2 >= pow(radius - Game::sharedGame()->getPlayer()->radius, 2)*1.2) return; // 没有吞并
    if(weight < Game::sharedGame()->getPlayer()->getBallWeight()) {
        // 被player吃掉
        Game::sharedGame()->getPlayer()->updateWeight(weight);
        Game::sharedGame()->getPlayer()->eatAINum++;
        Game::sharedGame()->AIBallArray.eraseObject(this);
        Game::sharedGame()->removeChild(this);
    }else if (weight > Game::sharedGame()->getPlayer()->getBallWeight()) {
        updateWeight(Game::sharedGame()->getPlayer()->getBallWeight());
        eatAINum++;
        // 主角死亡,通知Game
        Game::sharedGame()->playerKilled();
    }
    
}

#pragma mark -工具函数

void AIBall::updateWeight(int addedWeight) {
    if (weight + addedWeight < minWeight) return;
    weight += addedWeight;
    // 半径
    radius = sqrt(weight*Game::sharedGame()->scale);
    
    label_tag->setPosition(Vec2(0, radius+label_tag->getContentSize().height));
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
