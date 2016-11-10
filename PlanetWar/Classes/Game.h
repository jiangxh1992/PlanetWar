//
//  Game.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#ifndef __PlanetWar__Game__ 
#define __PlanetWar__Game__

class Game : public cocos2d::Layer {
  
/** 重写函数 **/
public:
	// 创建类对象
	static cocos2d::Scene* createScene();
	// 对象初始化
	virtual bool init();
    CREATE_FUNC(Game);
    
/** 内部变量和函数 **/
private:
    // 添加UI
    void addUI();
    // 返回到菜单页面
    void back(cocos2d::Ref* pSender);
};

#endif /* defined(__PlanetWar__Game__) */
