//
//  MenuScene.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#ifndef __PlanetWar__MenuScene__ 
#define __PlanetWar__MenuScene__

class MenuScene : cocos2d::Layer {
public:
    // 创建对象
    static cocos2d::Scene* createScene();
    // 对象初始化
    virtual bool init();
    CREATE_FUNC(MenuScene);
    
    // 进入场景
    //void onEnter();
    // 场景退出
    void onExit();
    
    // 开始游戏
    void startGame(cocos2d::Ref* pSender);
};

#endif /* defined(__PlanetWar__MenuScene__) */
