//
//  Const.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 24/11/16.
//
//

#ifndef Const_h
#define Const_h
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
// 游戏时间
extern const int maxSeconds;


/** 状态机状态 **/
typedef enum {
    IDLE_NORMAL,
    RUN_NORMAL,
    OVER_MAP
}PLAYER_STATE;

/* 工厂函数类型 */
typedef enum {
    BALL_BASE,
    BALL_AI,
    BALL_DEMON,
    BALL_BULLET
}FACTORY_TYPE;

/* 游戏模式 */
typedef enum {
    GAME_TIMER,    // 计时模式
    GAME_UNLIMITED // 无限模式
}GAME_TYPE;

#endif /* Const_h */
