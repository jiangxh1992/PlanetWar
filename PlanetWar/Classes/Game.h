//
//  Game.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#ifndef __PlanetWar__Game__ 
#define __PlanetWar__Game__
#include "PlayerBall.h"
#include "StaticBall.h"
USING_NS_CC;

class Game : public Layer {
  
/** 重写函数 **/
public:
	// 创建类对象
	static Scene* createScene();
	// 对象初始化
	virtual bool init();
    CREATE_FUNC(Game);
    // 安帧更新
    virtual void update(float time);
    // 图形绘制函数
    virtual void draw(Renderer*renderer, const Mat4& transform, uint32_t flags);
    // 退出
    void onExit();
    // 析构函数
    virtual ~Game();
    
/** 内部变量和函数 **/
private:
    
    // 玩家
    PlayerBall *player;
    // 状态机
    int CurState;
    // 触摸起始点和结束点
    Vec2 startPoint = Vec2::ZERO;
    Vec2 endPoint = Vec2::ZERO;
    // DrawNode
    DrawNode *drawNode;
    
    // debug txt
    Label *debuglabel;
    // 按钮菜单
    Menu *menu;
    
    // baseball 多边形数组
    Point **polyData;

    
    // 游戏变量初始化
    void initData();
    // 添加UI
    void addUI();
    // BaseBall工厂函数
    void createBaseBalls(int num);
    // AIBall工厂函数
    void createAIBAlls(int num);
    // 定时生成小球
    void createBaseBallTimer(float delta);
    // 屏幕缩放(0<scale<1)
    void scaleScreen(float scale);
    // 返回到菜单页面
    void back(Ref* pSender);
    // 加速
    void dash(Ref* pSender);
    // 注册屏幕触摸事件
    void addTouchListener();
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
    // 游戏观察者（检测吞并情况）
    void gameObserver(float delta);

/** 对外接口 **/
public:
    
    // 缩放参数
    float scale;
    
    // 游戏场景单例
    static Game* sharedGame();
    // UI layer
    LayerColor *uilayer;
    // 数组
    // staticball数组
    StaticBall *staticArray;
    // AIBall数组
    Vector<AIBall*> AIBallArray;
    
    // setter
    void setState(const int state) { CurState = state; }

    // getter
    const int getState() { return CurState; }
    const PlayerBall* getPlayer() { return player; }

};

#endif /* defined(__PlanetWar__Game__) */
