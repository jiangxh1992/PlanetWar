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
    label_tag->setGlobalZOrder(-100000);
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
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glEnable(GL_BLEND);
    if (isDraw) {
        // 绘制实心圆形
        drawNode->drawDot(Vec2(0, 0), radius, color);
        drawNode->drawDot(Vec2(0, 0), radius*0.9, Color4F(1.0, 1.0, 1.0, 0.2));
        drawNode->drawCircle(Vec2(0, 0), radius, 360, radius, false, Color4F(color.r, color.g, color.b, 0.5));
        // 根据球的半径更新当前球的绘制深度，半径越大的绘制在前面覆盖更小的球
        drawNode->setGlobalZOrder(radius-100000);
    }
}

/**
 * 安帧更新
 */
void AIBall::update(float time) {
    checkExplode();
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
    if(position.x >= maxW || position.x <= -(maxW)) {
        position -= direction * speed;
        direction.x = -direction.x;
        direction.y = CCRANDOM_0_1();
        direction.normalize();
    }else if(position.y >= maxH || position.y <= -(maxH)) {
        position -= direction * speed;
        direction.y = -direction.y;
        direction.x = CCRANDOM_0_1();
        direction.normalize();
    }
    // 矫正
    if(position.x > maxW) position.x = maxW-1;
    if(position.x < -maxW) position.x = -maxW+1;
    if(position.y > maxH) position.y = maxH-1;
    if(position.y < -maxH) position.y = -maxH+1;

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
    
    // 3.检测吞并player
    int playerWeight = Game::sharedGame()->getPlayer()->getBallWeight();
    if(Game::sharedGame()->getPlayer()->isVisible() && weight > playerWeight) {
        
        // AIBall与player的距离的平方
        double D2 = pow(Game::sharedGame()->getPlayer()->getPos().x -  position.x, 2) + pow(Game::sharedGame()->getPlayer()->getPos().y - position.y, 2);
        // 吞并距离
        float playerR = Game::sharedGame()->getPlayer()->getR();
        float minD =  radius - playerR*0.8;
        if (D2 < minD*minD) {
            updateWeight(Game::sharedGame()->getPlayer()->getBallWeight());
            eatAINum++;
            // 主角死亡,通知Game
            Game::sharedGame()->playerKilled();
        }
    }

    // 回收池
    Vector<AIBall*> autoreleasepool = Vector<AIBall*>();
    // 3.检测AIBall互相吞并
    for (Vector<AIBall*>::const_iterator it = Game::sharedGame()->AIBallArray.begin(); it != Game::sharedGame()->AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        if (weight <= aiball->getBallWeight()) continue; // 排除吞并自己以及比自己大的
        // 距离的平方
        double distance2 = pow(aiball->getPos().x -  position.x, 2) + pow(aiball->getPos().y - position.y, 2);
        // 吞并距离
        float minD = radius-aiball->radius*0.8;
        if (distance2 < minD*minD) {
            // 当前AIBall吞并对方
            updateWeight(aiball->getBallWeight());
            eatAINum++;
            autoreleasepool.pushBack(aiball);
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

AIBall::~AIBall() {
    this->unscheduleUpdate();
    this->unscheduleAllCallbacks();
}

#pragma mark -工具函数

void AIBall::updateWeight(int addedWeight) {
    if (weight + addedWeight < minWeight) {
        weight = minWeight;
        return;
    };
    weight += addedWeight;
    // 半径
    radius = sqrt(weight*Game::sharedGame()->scale);
    
    label_tag->setPosition(Vec2(0, radius+label_tag->getContentSize().height));
}

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

void AIBall::checkExplode() {
    if (radius > ScreenHeight/4) {
        // 爆炸粒子
        ParticleSystemQuad *explode = ParticleSystemQuad::create("particle_explode.plist");
        explode->setPosition(position);
        Game::sharedGame()->addChild(explode);
        Game::sharedGame()->AIBallArray.eraseObject(this);
        Game::sharedGame()->removeChild(this);
    }
}
