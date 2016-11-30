//
//  StaticBall.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 24/11/16.
//
//  静止的球

#ifndef __PlanetWar__StaticBall__ 
#define __PlanetWar__StaticBall__
USING_NS_CC;

class StaticBall {
public:    
    // 是否存活
    bool isActive;
    // 坐标
    Vec2 position = cocos2d::Vec2::ZERO;
    // 半径
    float radius = 0;
    // 边数
    int polyNum = 3;
    // 顶点数组
    Point *vertexs;
    // 颜色
    Color4F color = cocos2d::Color4F::YELLOW;
    // 重量
    int weight = 5;
    
    // 构造
    StaticBall();
    // 重新激活
    void reActive();
    // 缩放
    void scale(float scale);
    
    // 析构
    ~StaticBall();
    
};

#endif /* defined(__PlanetWar__StaticBall__) */
