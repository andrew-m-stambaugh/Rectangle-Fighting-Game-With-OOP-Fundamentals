

#include "Main.hxx"
#include <algorithm>

using namespace ge211;

Main::Main(
        Posn<float> position, ge211::Dims<float> velocity, int HP, bool
        invincible, bool hitbox_status,
        bool jump, bool left)
        : position_(position),
          hurtbox_(position.x - 15, position.y - 50,30,50),
          right_inactive_hitbox_(hurtbox_.center().x + hurtbox_.width/2, hurtbox_.center().y - 25,7,
                                 25),
          right_active_hitbox_(hurtbox_.center().x + hurtbox_.width/2 , position.y - hurtbox_.height/2 - 7, 25,
                               7),
          left_inactive_hitbox_(hurtbox_.center().x - hurtbox_.width/2 - 7, hurtbox_.center().y - 25, 7,
                                25),
          left_active_hitbox_(hurtbox_.center().x - hurtbox_.width/2 - 25, position.y - hurtbox_.height/2 - 7,
                              25, 7),
          velocity_(velocity),
          HP_(HP),
          invincible_(invincible),
          hitbox_status_(hitbox_status),
          jump_(jump),
          left_or_not_(left)
{  }

ge211::Posn<float>
Main::position() const
{
    return position_;
}

bool
Main::left_or_not() const
{
    return left_or_not_;
}

ge211::Dims<float>
Main::velocity() const
{
    return velocity_;
}

ge211::Rect<int>
Main::hurtbox() const
{
    return hurtbox_;
}

ge211::Rect<int>
Main::left_active_hitbox() const
{
    return left_active_hitbox_;
}

ge211::Rect<int>
Main::right_active_hitbox() const
{
    return right_active_hitbox_;
}

ge211::Rect<int>
Main::left_inactive_hitbox() const
{
    return left_inactive_hitbox_;
}

ge211::Rect<int>
Main::right_inactive_hitbox() const
{
    return right_inactive_hitbox_;
}


int
Main::HP() const
{
    return HP_;
}

bool
Main::hitbox_active() const
{
    return hitbox_status_;
}

bool
Main::invincibility() const
{
    return invincible_;
}

bool
Main::jump() const
{
    return jump_;
}

