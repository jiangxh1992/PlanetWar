//
//  StaticBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 24/11/16.
//
//

#include "StaticBall.h"
#include "Game.h"

StaticBall::StaticBall() {
    reActive();
}

void StaticBall::reActive() {
    // 默认活跃
    isActive = true;
    // 随机位置
    position = Vec2((CCRANDOM_0_1()*2-1) * maxW, (CCRANDOM_0_1()*2-1) * maxH);
    // 半径
    radius = 5*Game::sharedGame()->scale;
    // 随机颜色
    color = Color4F(255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 1.0);
}
