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
    bool isActive;                   // 是否存活
    Vec2 position = Vec2::ZERO;      // 坐标
    float radius = 0;                // 半径
    int polyNum = 3;                 // 边数
    Point *vertexs;                  // 顶点数组
    Color4F color = Color4F::YELLOW; // 颜色
    int weight = 5;                  // 重量
    
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
