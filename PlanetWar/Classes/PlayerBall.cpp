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
        direction = Vec2::ZERO;
    }
    
    // 2.移动
    if (std::abs(direction.x) < 0.01f || std::abs(direction.y) < 0.01f) {
        return;
    }
    position += direction * speed;
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
 * 加速
 */
void PlayerBall::speedUp() {
    isSpeedUp = true;
}

void PlayerBall::endSpeedUp() {
    isSpeedUp = false;
}

/**
 * 析构函数
 */
PlayerBall::~PlayerBall() {
}
