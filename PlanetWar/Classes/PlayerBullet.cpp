//
//  PlayerBullet.cpp
//  PlanetWar
//
//  Created by Xinhou Jiang on 1/12/16.
//
//

#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() {
}

PlayerBullet::PlayerBullet(Vec2 _position, Vec2 _direction) {
    position = _position;
    direction = _direction;
    color = Color4F(10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 1.0);
    power = 1;       // 威力
    radius = 2;    // 半径
    speed = 2;     // 速度
}

PlayerBullet::PlayerBullet(Vec2 _position, Vec2 _direction, int _power) {
    PlayerBullet( _position, _direction);
    power = _power;
    color = Color4F(10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 10+245*CCRANDOM_0_1(), 1.0);
    radius = power;// 半径
    speed = 2;     // 速度
}

PlayerBullet::PlayerBullet(Vec2 _position, Vec2 _direction, int _power, Color4F _color) {
    PlayerBullet(_position, _direction, _power);
    color = _color;
    radius = power;    // 半径
    speed = 2;     // 速度
}

PlayerBullet::~PlayerBullet(){}
