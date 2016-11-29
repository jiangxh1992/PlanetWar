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
    radius = 5;
    reActive();
}

void StaticBall::reActive() {
    // 默认活跃
    isActive = true;
    // 随机位置
    position = Vec2((CCRANDOM_0_1()*2-1) * maxW, (CCRANDOM_0_1()*2-1) * maxH);
    // 随机颜色
    color = Color4F(10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 1.0);
}

void StaticBall::scale(float scale) {
    radius *= scale;
    position *= scale;
}
