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
#include "Demon.h"
#include "PlayerBullet.h"
#include <vector>
using namespace std;
USING_NS_CC;

/* 背景星星数据结构 */
typedef struct {
    Vec2 position;
    float radius;
    Color4F color;
}STAR;


class Game : public Layer {
    
    /** 重写函数 **/
public:
    // 创建游戏场景
    static Scene* createScene(GAME_TYPE type);
    // 创建游戏对象
    static Game* create(GAME_TYPE type);
    // 对象初始化
    virtual bool init();
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
    
    // 游戏数据
    Scene *curScene;                  // 场景引用
    PlayerBall *player;               // 玩家
    int CurState;                     // 状态机
    Vec2 startPoint = Vec2::ZERO;     // 触摸起始点
    Vec2 endPoint = Vec2::ZERO;       // 触摸结束点
    Point Vertexs[4];                 // 边界顶点数组
    int timeCount = 0;                // 游戏倒计时
    int kill = 0;                     // 杀死demon数量
    GAME_TYPE gameType = GAME_TIMER;  // 游戏模式（默认倒计时模式）
    float gameLevel = 1.0;            // 游戏难度
    float dashCount = 100;              // 加速功能恢复计时
    
    // UI
    Menu *menu;          // 按钮菜单
    Label *debuglabel;   // debug txt
    Label *label_weight;
    Label *label_scale;
    Label *label_ainum;
    Label *label_basenum;
    Label *label_demon;
    Label *label_time;
    ProgressTimer *dashTimer;
    DrawNode *drawNode;  // DrawNode
    
    
    // 工具函数
    void initColorArray();
    void initData();                       // 游戏变量初始化
    void addUI();                          // 添加UI
    void addRoles();                       // 添加游戏角色
    void createBallFactory(FACTORY_TYPE type, int num); //Ball工厂函数
    void createBaseBalls(int num);         // BaseBall工厂
    void createBullet();                   // 子弹工厂
    void createAIBAlls(int num);           // AIBall工厂
    void createDemonBalls(int num);        // Demonball工厂
    void createBaseBallTimer(float delta); // 定时生成小球
    void gameObserver(float delta);        // AI调整
    void gametimer(float delta);           // 计时器
    void scaleScreen(float scale);         // 屏幕缩放(0<scale<1)
    void gameOver();                       // 游戏结束
    bool updateData(string new_name, int new_weight, int new_baseball, int new_aiball, int new_demon);// 数据持久化
    
    // 事件函数
    void back(Ref* pSender);
    void dash(Ref* pSender);
    void shoot(Ref* pSender);
    void scaleup(Ref* pSender);
    void scaledown(Ref* pSender);
    void playerReactive();                 // player复活
    void reStartGame(Ref* pSender);        // 重新游戏
    
    // 注册屏幕触摸事件
    void addTouchListener();
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
    
    /** 对外接口 **/
public:
    
    Color4F ColorArray[colorNum];      // 颜色库
    bool isGameOver = false;
    int baseNum = maxBaseBallNum;      // baseball个数
    float scale;                       // 缩放参数
    static Game* sharedGame();         // 游戏场景单例
    LayerColor *uilayer;               // UI layer
    LayerColor *bglayer1;              // 背景层1
    LayerColor *bglayer2;              // 背景层2
    StaticBall *staticArray;           // staticball数组
    vector<PlayerBullet> bulletArray;  // 子弹数组
    Vector<AIBall*> AIBallArray;       // AIBall数组
    Vector<Demon*> DemonArray;         // DemonBall数组
    
    // setter
    void setState(const int state) { CurState = state; }
    
    // getter
    int getState(){ return CurState; }
    PlayerBall* getPlayer()const{ return player; }
    Scene* getScene()const{return curScene;}
    
    // 外部事件通知
    void demonKilled(Demon *demon);        // 杀死demon事件
    void playerKilled();                   // 主角死亡事件
    void dashFinished();                   // 加速结束
    
};

#endif /* defined(__PlanetWar__Game__) */
