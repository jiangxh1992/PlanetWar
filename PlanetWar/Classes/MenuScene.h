//
//  MenuScene.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
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
    
    // 动态UI引用
    Sprite *label_title;
    MenuItemImage *item_startgame;
    MenuItemImage *item_history;
    Sprite *menu_bg;
    LayerColor *history_layer_bg;
    float scaleCount = 0;
    
    // 添加UI
    void addUI();
    void addHistoryUI();
    
    // 事件函数
    void startGame(Ref* pSender);
    void openHistory(Ref* pSender);
    void showLimitedRecord(Ref* pSender);
    void showUnLimitedRecord(Ref* pSender);
    void hideHistory(Ref* pSender);
};

#endif /* defined(__PlanetWar__MenuScene__) */
