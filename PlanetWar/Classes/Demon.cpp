//
//  Demon.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 30/11/16.
//
//

#include "Demon.h"
#include "StaticBall.h"
#include "Game.h"
USING_NS_CC;

Demon* Demon::create() {
	Demon *sprite = new Demon();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool Demon::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    commenInit();
    
    // 开启安帧更新
    this->scheduleUpdate();
    // 开启定时器
    this->schedule(schedule_selector(Demon::thisUpdate), Interval);
    
    return true;
}

/**
 * 绘图
 */
void Demon::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
    if (isDraw) {
        // 清空之前的绘制
        drawNode->clear();
        //启用混合
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glEnable(GL_BLEND);
        // 绘制实心圆形
        drawNode->drawDot(Vec2(0, 0), radius, color);
        // 随机颜色
        Color4F eagecolor = Color4F(10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 1.0);
        drawNode->drawCircle(Vec2(0, 0), radius*2, 360, radius*2, true, eagecolor);
        // 根据球的半径更新当前球的绘制深度，半径越大的绘制在前面覆盖更小的球
        drawNode->setGlobalZOrder(radius);
    }
}

/**
 * 碰撞检测重写
 */
void Demon::sharedUpdate(float delta) {
    
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
    
    // 2.检测攻击player
    Point p = Game::sharedGame()->getPlayer()->getPosition();
    double pr = Game::sharedGame()->getPlayer()->getR();
    float R2 = pow(radius + pr, 2.0);
    float D2 = pow((p.x - position.x), 2.0) + pow(p.y - position.y, 2.0);
    if (D2 < R2) {
        Game::sharedGame()->getPlayer()->setWeightBySub(3);
    }
    
    // 3.检测子弹碰撞
    

}

Demon::~Demon() {
}
