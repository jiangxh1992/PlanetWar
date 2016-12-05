//
//  Const.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 25/11/16.
//
//

#include <Const.h>

// 游戏场景边界
const int maxWidth = 1800;
const int maxHeight = 1300;
int maxW = maxWidth;
int maxH = maxHeight;

// 设计分辨率
const int designW = 568;
const int designH = 320;

// 移动间隔时间
const float Interval = 0.005;
// PI
const double PI = 3.1415926;
// 能量常量
const int Energy = 3000;
// 重量下限(初始重量)
const int minWeight = 300;
// 屏幕静止小球的数量上限
const int maxBaseBallNum = 1200;
// AI球的数量上限
const int maxAIBallNum = 30;
// 最大speed（这个实际为移动步长，不能太大，否则移动看上去会不流畅）
const int maxSpeed = 1;
// TIMER模式游戏初始时间限制
const int maxSeconds = 60;
