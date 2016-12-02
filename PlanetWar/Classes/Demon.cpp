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
#include <SimpleAudioEngine.h>
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
    // 清空之前的绘制
    drawNode->clear();
    //启用混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    if (isDraw) {
        // 绘制实心圆形
        drawNode->drawDot(Vec2(0, 0), radius, color);
        drawNode->drawDot(Vec2(0, 0), radius*0.9, Color4F(1.0, 1.0, 1.0, 0.2));
        // 随机颜色
        Color4F eagecolor = Color4F(10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 1.0);
        drawNode->drawCircle(Vec2(0, 0), radius*2, 360, radius*2, true, eagecolor);
        // 根据球的半径更新当前球的绘制深度，半径越大的绘制在前面覆盖更小的球
        // drawNode->setGlobalZOrder(radius);
        drawNode->setLocalZOrder(radius);
    }
}

/**
 * 碰撞检测重写
 */
void Demon::sharedUpdate(float delta) {
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
    
    // 2.检测攻击player
    Point p = Game::sharedGame()->getPlayer()->getPosition();
    double pr = Game::sharedGame()->getPlayer()->getR();
    float R2 = pow(radius + pr, 2.0);
    float D2 = pow((p.x - position.x), 2.0) + pow(p.y - position.y, 2.0);
    if (D2 < R2) {
        // player减体重
        Game::sharedGame()->getPlayer()->updateWeight(-3);
        // 自己减体重
        //updateWeight(-6);
        // 震动
        //CocosDenshion::SimpleAudioEngine::getInstance()->vibrate();
    }
    
    // 3.检测子弹碰撞
    for (int i =0; i < Game::sharedGame()->bulletArray.size(); i++) {
        Point p = Game::sharedGame()->bulletArray[i].getPos();
        float r = Game::sharedGame()->bulletArray[i].getRadius();
        double D2 = pow(p.x - position.x, 2.0) + pow(p.y - position.y, 2.0);
        double R2 = pow((r + radius), 2.0);
        if (D2 < R2) {
            // 减血
            updateWeight(-Game::sharedGame()->bulletArray[i].getPower());
            // 销毁子弹
            Game::sharedGame()->bulletArray.erase(Game::sharedGame()->bulletArray.begin() + i);
        }
    }

}

void Demon::updateWeight(int addedWeight) {
    weight += addedWeight;
    // 半径
    radius = sqrt(weight*Game::sharedGame()->scale);
    
    label_tag->setPosition(Vec2(0, radius*2+label_tag->getContentSize().height));
    
    // 死亡
    if (weight < 50) {
        // 通知Game
        Game::sharedGame()->demonKilled(this);
    }
    
    // 爆炸粒子特效
    // 。。。
}

Demon::~Demon() {
}
