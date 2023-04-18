//*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "Enemy.hxx"
#include <algorithm>

using namespace ge211;
Enemy::Enemy()
        : position_(0,0),
          hurtbox_(0,0,0,0),
          hitbox_(0,0,0,0),
          velocity_(0,0),
          HP_(30),
          invincible_(false),
          hitbox_status_(false),
          inv_timer_(0)
{ }

Enemy::Enemy(ge211::Posn<float> position, ge211::Dims<float> velocity, int HP,
             bool invincible, bool hitbox_status,
             int inv_timer)
        : position_(position),
          hurtbox_(position.x - 15, position.y - 50,30,50),
          hitbox_(position.x - 15, position.y - 50,30,50),
          velocity_(velocity),
          HP_(HP),
          invincible_(invincible),
          hitbox_status_(hitbox_status),
          inv_timer_(inv_timer)
{  }

ge211::Posn<float>
Enemy::position() const
{
    return position_;
}


int
Enemy::inv_timer() const
{
    return inv_timer_;
}

ge211::Dims<float>
Enemy::velocity() const
{
    return velocity_;
}

ge211::Rect<int>
Enemy::hurtbox() const
{
    return hurtbox_;
}

ge211::Rect<int>
Enemy::hitbox() const
{
    return hitbox_;
}

int
Enemy::HP() const
{
    return HP_;
}

bool
Enemy::hitbox_active() const
{
    return hitbox_status_;
}

bool
Enemy::invincibility() const
{
    return invincible_;
}
