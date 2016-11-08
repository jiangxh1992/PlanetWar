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
	// 创建类对象
	static cocos2d::Scene* createScene();
	// 对象初始化
	virtual bool init();
    CREATE_FUNC(Game);
};

#endif /* defined(__PlanetWar__Game__) */
