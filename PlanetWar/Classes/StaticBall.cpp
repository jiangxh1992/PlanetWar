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
    // 生成随机边数3\4\5
    polyNum = 3 + CCRANDOM_0_1()*3;
    // 计算顶点数组
    vertexs = new Point[polyNum];
    for (int i = 0; i<polyNum; i++) {
        vertexs[i].x = position.x + radius * cos(2*PI*i/polyNum);
        vertexs[i].y = position.y + radius * sin(2*PI*i/polyNum);
    }
}

void StaticBall::scale(float scale) {
    radius *= scale;
    position *= scale;
    // 更新顶点数组
    for (int i = 0; i<polyNum; i++) {
        vertexs[i].x = position.x + radius * cos(2*PI*i/polyNum);
        vertexs[i].y = position.y + radius * sin(2*PI*i/polyNum);
    }
}

StaticBall::~StaticBall(){
    // 释放堆内存
    //delete [] vertexs;
}
