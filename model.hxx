/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// This model tracks the state of everything in the game including the
// main player and the enemies. It also keeps track of how long certain states
// have been true, and makes them false if they've been true for a certain
// amount of time.

#pragma once

#include "Main.hxx"
#include "Enemy.hxx"
#include "Items.hxx"
#include <vector>

// The logical state of the game.
struct Model
{
    ///
    /// CONSTRUCTOR
    ///
    explicit Model();

    ///
    /// MEMBER FUNCTIONS
    ///

    // Main player functions
    // Puts the character into jump mode
    void make_jump(bool value);
    // Changes the x component of the main's velocity
    void change_x_velocity(float x_velocity);
    // Changes the y component of the main's velocity
    void change_y_velocity(double dt);
    // Swings or retracts the sword to activate its hitbox
    void swing_retract_sword(bool value);
    // Does damage to the main character of the given input
    void do_damage_main(int damage);

    // Enemy functions
    // Increments the invincibility timer of the given enemy
    Enemy inc_inv_timer(Enemy curr_enemy);
    // Does the given amount of damage to the given enemy
    Enemy do_damage_en(Enemy curr_enemy, int damage);
    // Check that all enemies have spawned and that all are dead
    bool all_dead(std::vector<Enemy> Enemies);

    // Helper functions
    // Given the top left and bottom right positions of two rectangles.
    // Returns true if the two rectangles are overlapping at all
    bool doOverlap(ge211::Posn<int> l1, ge211::Posn<int> r1, ge211::Posn<int> l2, ge211::Posn<int> r2);

    void on_frame(double dt);

    ///
    /// MEMBER VARIABLES
    ///


    // The state of the main player
    Main main;

    std::vector<Enemy> enemies;

    // for (int i = 0; i < 8; i++) {
    //     enemies.insert(Enemy());
    // }

    // The bools for checking whether the a and d keys are pressed
    bool a_key;
    bool d_key;
    // The two functions that update whether the a and d keys are being pressed
    void a_pressed(bool value);
    void d_pressed(bool value);

    // Whether the game is over or not
    bool over;
    bool win;

    // bool for whether the game is paused, and the function that pauses or
    // unpauses the game
    bool paused;
    void pause();

    // The heart and freeze objects which keep track of the heart or freeze
    // in current existence. There can only be one
    Heart heart;
    Freeze freeze;

    // Whether the enemies are frozen or not
    bool frozen;

    // Counts the number of enemies that have spawned. Doesn't go down if
    // enemies die
    int enemy_counter;

    // Increments each frame
    int counter;
};

