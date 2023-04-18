

// Defines the class for the main character

#pragma once

#include <ge211.hxx>

#include <iostream>

class Main
{
public:
    Main(ge211::Posn<float> position, ge211::Dims<float> velocity, int HP,
            bool invincible, bool hitbox_status, bool jump, bool left);
    /// Returns player's position
    ge211::Posn<float> position() const;

    /// Returns player's hurtbox
    ge211::Rect<int> hurtbox() const;

    /// Returns player's right inactive hitbox
    ge211::Rect<int> right_inactive_hitbox() const;
    /// Returns player's right active hitbox
    ge211::Rect<int> right_active_hitbox() const;
    /// Returns player's left inactive hitbox
    ge211::Rect<int> left_inactive_hitbox() const;
    /// Returns player's left active hitbox
    ge211::Rect<int> left_active_hitbox() const;


    /// Returns player's hitbox
    ge211::Dims<float> velocity() const;

    /// Returns player's HP
    int HP() const;

    /// Returns player's invinciblity status
    bool invincibility() const;

    /// Returns player's jump status
    bool jump() const;

    /// Returns player's hitbox status
    bool hitbox_active() const;

    /// Returns if object is moving left or not
    bool left_or_not() const;


private:

    /// The center of the main character's hurtbox, indicating position
    ge211::Posn<float> position_;

    /// The character's hurtbox size
    ge211::Rect<int> hurtbox_;

    /// character's hitbox when inactive and facing left
    ge211::Rect<int> right_inactive_hitbox_;

    /// character's hitbox when active and facing left
    ge211::Rect<int> right_active_hitbox_;

    /// character's hitbox when inactive and facing right
    ge211::Rect<int> left_inactive_hitbox_;

    /// character's hitbox when active and facing right
    ge211::Rect<int> left_active_hitbox_;

    /// The character's velocity
    ge211::Dims<float> velocity_;

    /// Character's HP
    int HP_;

    /// Whether the character is invincible or not
    bool invincible_;

    /// Whether the character's hitbox is active or not
    bool hitbox_status_;

    /// Is the character in the air or not
    bool jump_;

    /// Is the character moving left or right
    bool left_or_not_;

};