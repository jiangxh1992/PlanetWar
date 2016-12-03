//
//  MenuScene.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//  数据key:
//  1.timer_name, timer_weight, timer_baseball, timer_aiball, timer_demon
//  2.unlimited_name,unlimited_weight, unlimited_baseball, unlimited_aiball, unlimited_demon
//

#ifndef __PlanetWar__MenuScene__ 
#define __PlanetWar__MenuScene__
USING_NS_CC;

class MenuScene : Layer {
public:
    // 创建对象
    static Scene* createScene();
    // 对象初始化
    virtual bool init();
    // 安帧更新
    virtual void update(float time);
    CREATE_FUNC(MenuScene);
    // 场景退出
    void onExit();
    
    float scaleCount = 0;
    
    // 动态UI引用
    Sprite *label_title;
    MenuItemImage *item_startgame1;
    MenuItemImage *item_startgame2;
    MenuItemImage *item_history;
    Sprite *menu_bg;
    LayerColor *history_layer_bg;
    
    // History UI引用
    Label *label_history;
    Label *label_name;
    Label *label_weight;
    Label *label_demon;
    Label *label_base;
    Label *label_ai;
    
    // 添加UI
    void addUI();
    void addHistoryUI();
    
    // 事件函数
    void startGameTimer();
    void startGameUnlimited();
    void openHistory();
    void showLimitedRecord();
    void showUnLimitedRecord();
    void hideHistory();
    void updateHistory(__String new_name, int new_weight, int new_baseball, int new_aiball, int new_demon);
};

#endif /* defined(__PlanetWar__MenuScene__) */
