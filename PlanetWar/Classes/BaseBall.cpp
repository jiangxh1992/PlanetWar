//
//  BaseBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#include "BaseBall.h"
#include "Game.h"
USING_NS_CC;

/**
 * 绘图
 */
void BaseBall::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
    if (isDraw) {
        // 清空之前的绘制
        drawNode->clear();
        //启用混合
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glEnable(GL_BLEND);
        // 绘制实心圆形
        drawNode->drawDot(Vec2(0, 0), radius, color);
        // 根据球的半径更新当前球的绘制深度，半径越大的绘制在前面覆盖更小的球
        drawNode->setGlobalZOrder(radius);
    }
}

/**
 * 析构
 */
BaseBall::~BaseBall() {
}
