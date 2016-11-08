//
//  BaseBall.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 8/11/16.
//
//

#include "BaseBall.h"
USING_NS_CC;

BaseBall* BaseBall::create() {
	BaseBall *sprite = new BaseBall();
	if (sprite && sprite->init())
	{
        sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool BaseBall::init() {
    return true;
}
