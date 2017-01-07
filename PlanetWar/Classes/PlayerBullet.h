//
//  PlayerBullet.h
//  PlanetWar
//
//  Created by Xinhou Jiang on 1/12/16.
//
//  player子弹

#ifndef __PlanetWar__PlayerBullet__ 
#define __PlanetWar__PlayerBullet__
USING_NS_CC;

class PlayerBullet {
    
    Vec2 position;   // 位置
    Vec2 direction;  // 发射方向
    Color4F color;   // 颜色
    int power;       // 威力
    float radius;    // 半径
    float speed;     // 速度
public:
    // 构造函数
    PlayerBullet();
    PlayerBullet(const Vec2 _position, const Vec2 _direction);
    PlayerBullet(const Vec2 _position, const Vec2 _direction, const int _power);
    PlayerBullet(const Vec2 _position, const Vec2 _direction, const int _power, const Color4F _color);
    ~PlayerBullet();
    // 移动
    void move(){position += direction*speed;}
    
    // getter
    const Vec2 getPos()const{return position;}
    const Color4F getColor()const{return color;}
    const int getPower()const{return power;}
    const float getRadius()const{return radius;}
    const float getSpeed()const{return speed;}
    
    // setter
    void setPosition(const Vec2 _position){position = _position;}
    void setSpeed(const float _speed){speed = _speed;}
    void setDirction(const Vec2 _dir){direction = _dir;}
    void setRadius(const float _radius){radius = _radius;}
    void setColor(const Color4F _color){color = _color;}
    void setPower(const int _power){power = _power;}
};

#endif /* defined(__PlanetWar__PlayerBullet__) */
