//
//  BaseBall.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#ifndef __PlanetWar__BaseBall__ 
#define __PlanetWar__BaseBall__

class BaseBall : public cocos2d::Sprite {
	// 创建类对象
	static BaseBall* create();
    // 对象初始化
    virtual bool init();
    
};

#endif /* defined(__PlanetWar__BaseBall__) */
