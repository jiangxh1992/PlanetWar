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
extern int maxW;
extern int maxH;
extern const int maxWidth;
extern const int maxHeight;

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
// 屏幕小球的数量上限
extern const int maxBaseBallNum;
// AI球的数量上限
extern const int maxAIBallNum;
// 最大speed
extern const int maxSpeed;

/** 状态机状态 **/
typedef enum{
    IDLE_NORMAL,
    RUN_NORMAL,
    OVER_MAP
}PLAYER_STATE;




#endif /* Ball_h */
