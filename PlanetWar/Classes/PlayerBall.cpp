//
//  PlayerBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 14/11/16.
//
//

#include "PlayerBall.h"
#include "Game.h"
USING_NS_CC;
#define maxSpeedUp 1000

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
    commenInit();
    
    // 位置初始化在屏幕中心
    position = Vec2(VisiableSize.width/2, VisiableSize.height/2);
    // 设置位置
    setPosition(position);

    isSpeedUp = false;
    
    // 开启安帧更新
    this->scheduleUpdate();
    // 开启定时器
    this->schedule(schedule_selector(PlayerBall::thisUpdate), Interval);
    
    return true;
}

/**
 * 安帧更新
 */
void PlayerBall::update(float time) {
    sharedUpdate(time);
}

/**
 * 定时更新
 */
void PlayerBall::thisUpdate(float delta) {
    // 加速
    if (isSpeedUp) {
        speedUpCount++;
        // 加速结束
        if (speedUpCount>maxSpeedUp) {
            isSpeedUp = false;
            speedUpCount = 0;
            Game::sharedGame()->dashFinished();
        }
    }
    
    // 0.延迟检测
    speedInterval = 1+(double)weight/(double)minWeight/20;
    if (intervalCount < speedInterval && !isSpeedUp) {
        intervalCount += 0.2*Game::sharedGame()->scale;
        return;
    }else {
        intervalCount = 1.0;
    }
    
    // 1.RUN_NORMAL -> OVER_MAP
    if (position.x > maxW || position.x < -maxW || position.y > maxH || position.y < -maxH) {
        Game::sharedGame()->setState(OVER_MAP);
        // 矫正
        if(position.x >= maxW) position.x = maxW;
        if(position.x <= -maxW) position.x = -maxW;
        if(position.y >= maxH) position.y = maxH;
        if(position.y <= -maxH) position.y = -maxH;
        // 停止运动
        speedFactor = 0;
    }
    
    // 2.移动
    if (std::abs(direction.x) < 0.01f || std::abs(direction.y) < 0.01f) {
        return;
    }
    position += direction * speed * speedFactor;
    setPosition(position);// 本地坐标
    
    // 3.屏幕跟随
    Game::sharedGame()->getScene()->getDefaultCamera()->setPosition(position);
    // uilayer跟随相机
    Game::sharedGame()->uilayer->setPosition(position - Vec2(ScreenWidth/2, ScreenHeight/2));
    
    // 4.OVER_MAP -> RUN_NORMAL
    bool isNormal = position.x < maxW || position.x > -maxW || position.y < maxH || position.y > -maxH;
    if(isNormal) Game::sharedGame()->setState(RUN_NORMAL);

}

/**
 * 碰撞检测
 */
void PlayerBall::sharedUpdate(float delta) {
    if(Game::sharedGame()->isGameOver) return;
    // 检测吃小球
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
    // 3.检测吞并AIBall
    for (Vector<AIBall*>::const_iterator it = Game::sharedGame()->AIBallArray.begin(); it != Game::sharedGame()->AIBallArray.end(); it++) {
        AIBall *aiball = *it;
        if (weight < aiball->getBallWeight()) continue; // 排除比自己大的
        // 距离的平方
        double distance2 = pow(aiball->getPos().x -  position.x, 2) + pow(aiball->getPos().y - position.y, 2);
        // 吞并距离
        float minD = radius-aiball->getR()*0.8;
        if (distance2 < minD*minD) {
            // 吞并AIBall
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

/**
 * 加速
 */
void PlayerBall::speedUp() {
    isSpeedUp = true;
    speedUpCount = 0;
}

PlayerBall::~PlayerBall() {
}
