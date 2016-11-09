//
//  BaseBall.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#ifndef __PlanetWar__BaseBall__ 
#define __PlanetWar__BaseBall__

class BaseBall : public cocos2d::Sprite {
    
public:
	// 创建类对象
	static BaseBall* create();
    // 对象初始化
    virtual bool init();
    // 绘制图形
    virtual void draw(cocos2d::Renderer*renderer, const cocos2d::Mat4& transform, uint32_t flags);
    // 安帧更新
    virtual void update(float time);
    
private:
    // 坐标
    int x=0;
    int y=0;
    // 半径
    float radius=0;
    // 颜色
    cocos2d::Color4F color = cocos2d::Color4F::WHITE;
    // 移动方向
    cocos2d::Vec2 direction = cocos2d::Vec2::ZERO;
    // 移动速度
    int speed = 0;
    
    
    // 对外接口
public:
    int getX(){return x;}
    int getY(){return y;}
    float getR(){return radius;}
    
};

#endif /* defined(__PlanetWar__BaseBall__) */
