//
//  Ball.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 24/11/16.
//
//

#ifndef Ball_h
#define Ball_h

/** 常量 **/
// 游戏场景边界
extern const int maxW;
extern const int maxH;

// 设计分辨率
extern const int designW;
extern const int designH;

// 移动间隔时间
extern const float Interval;
// PI
extern const double PI;
// 能量常量
extern const int Energy;
// 重量下限
extern const int minWeight;
// 重量上限
extern const int maxWeight;
// 屏幕小球的数量上限
extern const int maxBaseBallNum;
// AI球的数量上限
extern const int maxAIBallNum;

/** 状态机状态 **/
typedef enum{
    IDLE_NORMAL,
    RUN_NORMAL,
    OVER_MAP
}PLAYER_STATE;


#endif /* Ball_h */
