//
//  PlayerBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 14/11/16.
//
//

#include "PlayerBall.h"
#include "Game.h"
#include "Ball.h"
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
    
    // label
    label_tag = Label::create();
    label_tag->setString("player");
    label_tag->setPosition(Vec2(0, radius+label_tag->getContentSize().height));
    addChild(label_tag);
    
    // 位置初始化在屏幕中心
    position = Vec2(VisiableSize.width/2, VisiableSize.height/2);
    // 初始重量
    updateWeight(minWeight);
    // 随机颜色
    color = Color4F(255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 255*CCRANDOM_0_1(), 1.0);
    // 随机图片
    // initWithFile("CloseNormal.png");
    // isDraw = false;
    
    // 步长
    speed = maxSpeed;
    // 移动间隔帧数
    speedInterval = 1.0f;
    // 间隔帧数计数器
    intervalCount = 0.9f;
    isSpeedUp = false;
    
    // 设置位置
    setPosition(position);
    // drawnode
    drawNode = DrawNode::create();
    this->addChild(drawNode);
    
    // 开启安帧更新
    this->scheduleUpdate();
    // 开启定时器
    this->schedule(schedule_selector(PlayerBall::sharedUpdate), Interval);// 继承自父类的更新
    this->schedule(schedule_selector(PlayerBall::thisUpdate), Interval/2);
    
    return true;
}

/**
 * 安帧更新
 */
void PlayerBall::update(float time) {}

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
    
    // 1.移动
    if (std::abs(direction.x) < 0.01f || std::abs(direction.y) < 0.01f) {
        return;
    }
    bool isEage = position.x >= maxW-radius || position.x <= radius-maxW || position.y >= maxH-radius || position.y <= radius-maxH;
    if(isEage) {
        position -= direction*speed*2;
        direction = Vec2::ZERO;
        setPosition(position);// 本地坐标
    }else {
        position += direction*speed;
        setPosition(position);// 本地坐标
    }
    
    // 2.RUN_NORMAL -> OVER_MAP
    if(Game::sharedGame()->getState() == RUN_NORMAL) {
        if (position.x >= maxW-ScreenWidth/2) {
            Game::sharedGame()->setState(OVER_MAP);
        }
        
        if (position.x <= ScreenWidth/2-maxW) {
            Game::sharedGame()->setState(OVER_MAP);
        }
        
        if (position.y >= maxH-ScreenHeight/2) {
            Game::sharedGame()->setState(OVER_MAP);
        }
        
        if (position.y <= ScreenHeight/2-maxH) {
            Game::sharedGame()->setState(OVER_MAP);
        }
        
    }
    // 3.屏幕跟随
    if (Game::sharedGame()->getState() != OVER_MAP) {
        Vec2 offset_p = position - Vec2(ScreenWidth/2, ScreenHeight/2);
        Vec2 offset_l = Game::sharedGame()->getPosition();
        Vec2 dir = offset_l + offset_p;
        int factor = dir.x + dir.y > 2 ? 1.2 : 1;
        dir.normalize();
        // 游戏场景移动
        Game::sharedGame()->setPosition(Game::sharedGame()->getPosition() - dir*factor*speed);
        // UILayer移动恢复
        Game::sharedGame()->uilayer->setPosition(Game::sharedGame()->uilayer->getPosition() + dir*factor*speed);
    }
    
    // 4.OVER_MAP -> RUN_NORMAL
    int curState = Game::sharedGame()->getState();
    bool isOverMap = position.x >= maxW-ScreenWidth/2 || position.x <= ScreenWidth/2-maxW || position.y >= maxH-ScreenHeight/2 || position.y <= ScreenHeight/2-maxH;
    if(curState == OVER_MAP && !isOverMap) {
        Game::sharedGame()->setState(RUN_NORMAL);
    }

}

/**
 * 缩放
 */
void PlayerBall::scale(float scale) {
    // postion
    position *= scale;
    // speed
    speedInterval /= scale;
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

void PlayerBall::setLabel(const cocos2d::__String label) {
    label_tag->setString(label._string);
}

/**
 * 析构函数
 */
PlayerBall::~PlayerBall() {
}
