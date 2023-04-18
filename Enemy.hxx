
//
// Created by ams1258 on 12/1/2022.
//

#pragma once

#include <ge211.hxx>

#include <iostream>

class Enemy
{
public:

    /// Constructors
    Enemy();
    Enemy(ge211::Posn<float> position, ge211::Dims<float> velocity, int HP, bool invincible,
          bool hitbox_status, int inv_timer);

    /// Returns Enemy's position
    ge211::Posn<float> position() const;

    /// Returns Enemy's hurtbox
    ge211::Rect<int> hurtbox() const;

    /// Returns Enemy's invincibility timer
    int inv_timer() const;

    /// Returns Enemy's right inactive hitbox
    ge211::Rect<int> hitbox() const;

    /// Returns Enemy's hitbox
    ge211::Dims<float> velocity() const;

    /// Returns Enemy's HP
    int HP() const;

    /// Returns Enemy's invinciblity status
    bool invincibility() const;

    /// Returns Enemy's hitbox status
    bool hitbox_active() const;

private:

    /// The center of the main character's hurtbox, indicating position
    ge211::Posn<float> position_;

    /// The character's hurtbox size
    ge211::Rect<int> hurtbox_;

    /// character's hitbox when inactive and facing left
    ge211::Rect<int> hitbox_;

    /// The character's velocity
    ge211::Dims<float> velocity_;

    /// Character's HP
    int HP_;

    /// Whether the character is invincible or not
    bool invincible_;

    /// Whether the character's hitbox is active or not
    bool hitbox_status_;

    /// Character's invincibility
    int inv_timer_;

};
