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
 * 初始化
 */
bool AIBall::init() {
    // 开启定时器
    this->schedule(schedule_selector(AIBall::fixedUpdate), Interval);
}

/**
 * 定时器
 */
void AIBall::fixedUpdate(float delta) {
    setPosition(Vec2(x, y)+direction);
}
