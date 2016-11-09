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

/** 重写函数 **/
public:
	// 创建类对象
	static BaseBall* create();
    // 对象初始化
    virtual bool init();
    // 绘制图形
    virtual void draw(cocos2d::Renderer*renderer, const cocos2d::Mat4& transform, uint32_t flags);
    // 安帧更新
    virtual void update(float time);

/** 内部变量和函数 **/
protected:
    // 坐标
    cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
    // 半径
    float radius = 0;
    // 颜色
    cocos2d::Color4F color = cocos2d::Color4F::YELLOW;
    // 重量
    int weight = 1;
    // DrawNode
    cocos2d::DrawNode *drawNode;
    
    
/** 对外接口 **/
public:
    // getter
    cocos2d::Vec2 getPos(){return position;}
    float getR(){return radius;}
    int getWeight(){return weight;}
    
    // setter
    void setWeight(int _weight){weight = _weight;}
};

#endif /* defined(__PlanetWar__BaseBall__) */
