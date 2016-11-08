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
    
public:
	// 创建类对象
	static BaseBall* create();
    // 对象初始化
    virtual bool init();
    
private:
    // 坐标
    int x;
    int y;
    
    
public:
    int getX(){return x;}
    int getY(){return y;}
    
};

#endif /* defined(__PlanetWar__BaseBall__) */
