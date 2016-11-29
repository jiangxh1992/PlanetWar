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
    // 绘制图形
    virtual void draw(cocos2d::Renderer*renderer, const cocos2d::Mat4& transform, uint32_t flags);
    // 析构函数
    virtual ~BaseBall();

/** 内部变量和函数 **/
protected:
    // 坐标
    cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
    // 半径
    double radius = 0;
    // 颜色
    cocos2d::Color4F color = cocos2d::Color4F::YELLOW;
    // 重量
    int weight = 1;
    // 是否启动图形绘制
    bool isDraw = true;
    // DrawNode
    cocos2d::DrawNode *drawNode = NULL;
    
/** 对外接口 **/
public:
    // getter
    const cocos2d::Vec2 getPos(){return position;}
    const float getR(){return radius;}
    const int getWeight(){return weight;}
    
    // setter
    void setWeight(const int _weight){weight = _weight;}
    
    // 缩放
    virtual void scale(const float scale){}
};

#endif /* defined(__PlanetWar__BaseBall__) */
