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
    
    // 数据
    PlayerBall *player;           // 玩家
    int CurState;                 // 状态机
    Vec2 startPoint = Vec2::ZERO; // 触摸起始点
    Vec2 endPoint = Vec2::ZERO;   // 触摸结束点
    //Point* polyData[3];         // baseball 多边形数组
    
    // UI
    Menu *menu;          // 按钮菜单
    Label *debuglabel;   // debug txt
    Label *label_weight;
    Label *label_scale;
    DrawNode *drawNode;  // DrawNode
    
    // 工具函数
    void initData();                       // 游戏变量初始化
    void addUI();                          // 添加UI
    void createBallFactory(FACTORY_TYPE type, int num); //Ball工厂函数
    void createBaseBalls(int num);         // BaseBall工厂
    void createAIBAlls(int num);           // AIBall工厂
    void createBaseBallTimer(float delta); // 定时生成小球
    void gameObserver(float delta);        // AI调整
    void scaleScreen(float scale);         // 屏幕缩放(0<scale<1)
    
    // 事件函数
    void back(Ref* pSender);
    void dash(Ref* pSender);
    void scaleup(Ref* pSender);
    void scaledown(Ref* pSender);
    
    // 注册屏幕触摸事件
    void addTouchListener();
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void onTouchCancelled(Touch *touch, Event *unused_event);

/** 对外接口 **/
public:
    
    float scale;                  // 缩放参数
    static Game* sharedGame();    // 游戏场景单例
    LayerColor *uilayer;          // UI layer
    StaticBall *staticArray;      // staticball数组
    Vector<AIBall*> AIBallArray;  // AIBall数组
    
    // setter
    void setState(const int state) { CurState = state; }

    // getter
    const int getState() { return CurState; }
    const PlayerBall* getPlayer() { return player; }

};

#endif /* defined(__PlanetWar__Game__) */
