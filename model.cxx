// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "model.hxx"

Model::Model()
        : main(ge211::geometry::Posn<float>(800/2,500),
                ge211::geometry::Dims<float>(0,0),
               100,false, false, false, false),
          a_key(false),
          d_key(false),
          over(false),
          win(false),
          paused(false),
        // Give the heart and freeze items positions which cannot be reached to
        // simulate there are none in the game
          heart(ge211::Rect<int>(1000,10000,0,0)),
          freeze(ge211::Rect<int>(1000,20000,0,0)),
          frozen(false),
          enemy_counter(0),
          counter(0)
{
}

// Pauses or unpauses the game, called by controller upon a press of the space bar
void
Model::pause()
{
    if (paused == true) {
        paused = false;
    } else {
        paused = true;
    }
}

// Tells the model whether the a key is being pressed or not. Called by the controller on key press and depress
void
Model::a_pressed(bool value)
{
    a_key = value;
}

// Tells the model whether the a key is being pressed or not. Called by the controller on key press and depress
void
Model::d_pressed(bool value)
{
    d_key = value;
}


// Swings the sword if not already swung, if given true. If given false, retracts the sword
void
Model::swing_retract_sword(bool value)
{
    if (main.hitbox_active()!= true) {
        main = Main(main.position(), main.velocity(), main.HP(),
                    main.invincibility(), value, main.jump(), main.left_or_not());
    } else {
        main = Main(main.position(), main.velocity(), main.HP(),
                    main.invincibility(), value, main.jump(), main.left_or_not());
    }
}

// Makes the character jump if not already in the air, if given true. If given false, updates the main character status
// so that the model knows they are no longer jumping.
void
Model::make_jump(bool value)
{
    if (value == true) {
        if (main.jump() != true) {
            float y = main.position().y-0.01;
            main = Main({main.position().x, y},
                        {main.velocity().width, 650}, main.HP(),
                        main.invincibility(),main.hitbox_active(), value, main.left_or_not());
        }
    } else {
        main = Main(main.position(), {main.velocity().width, 0}, main.HP(),
                    main.invincibility(),main.hitbox_active(), value, main.left_or_not());
    }

}

// Updates the x value of the main character's position to the given value
void
Model::change_x_velocity(float x_velocity)
{
    if (x_velocity < 0) {
        main = Main(main.position(), {x_velocity, main.velocity().height},
                    main.HP(), main.invincibility(), main.hitbox_active(),
                    main.jump(), true);
    } else if (x_velocity > 0) {
        main = Main(main.position(), {x_velocity, main.velocity().height},
                    main.HP(), main.invincibility(), main.hitbox_active(),
                    main.jump(), false);
    } else {
        main = Main(main.position(), {x_velocity, main.velocity().height},
                    main.HP(), main.invincibility(), main.hitbox_active(),
                    main.jump(), main.left_or_not());
    }
}

// Updates the y value of the main characters velocity
void
Model::change_y_velocity(double dt)
{
    float y = main.velocity().height - 9.8 * dt * 200;
    main = Main(main.position(), {main.velocity().width, y},
                main.HP(), main.invincibility(), main.hitbox_active(),
                true, main.left_or_not());
}

// Does damage to the main player equal to the given value
void
Model::do_damage_main(int damage){
    main = Main(main.position(), main.velocity(),main.HP() - damage, true,
                main.hitbox_active(),main.jump(),main.left_or_not());
}

// Enemy functions

// Increments the enemy's invincibility timer
Enemy
Model::inc_inv_timer(Enemy curr_enemy)
{
    return Enemy(curr_enemy.position(), curr_enemy.velocity(), curr_enemy.HP(),curr_enemy.invincibility(),
                 curr_enemy.hitbox_active(), curr_enemy.inv_timer() + 1);
}

// Does damage to an enemy equal to the given amount
Enemy
Model::do_damage_en(Enemy curr_enemy, int damage){
    return Enemy(curr_enemy.position(), curr_enemy.velocity(), curr_enemy.HP() - damage,
                 true,curr_enemy.hitbox_active(),curr_enemy.inv_timer());
}

// Checks whether every enemy is dead
bool
Model::all_dead(std::vector<Enemy> Enemies){

    if (enemy_counter == 13) {
        for (auto enemy_: Enemies) {
            if (enemy_.position().x != 10000) {
                return false;
            }
        } return true;
    }

    return false;
}




// Helper function for checking if hurtboxes overlap

// Returns true if two rectangles (l1, r1) and (l2, r2) overlap at all
bool
Model::doOverlap(ge211::Posn<int> l1, ge211::Posn<int> r1, ge211::Posn<int> l2, ge211::Posn<int> r2)
{
    // if rectangle has 0 area, no overlap
    if (l1.x == r1.x || l1.y == r1.y || r2.x == l2.x || l2.y == r2.y)
        return false;

    // If one rectangle is fully on the left of the other
    if (r1.x < l2.x || r2.x < l1.x)
        return false;

    // If one rectangle is fully above the other
    if (r1.y < l2.y || r2.y < l1.y)
        return false;

    return true;
}

// Counters to keep track of the time certain game states have been active
int hitbox_counter = 0;
int main_inv_counter = 0;
int freeze_counter = 0;

void
Model::on_frame(double dt)
{
    // Only update game if it's stil going, of course
    if (over == false) {

        // If game is paused, then do not update game and counter.
        if (paused != true) {

            ///
            /// Main Player Updates
            ///

            // Check to see if the a and d keys are pressed. Update x velocity accordling
            if (a_key == true && d_key == true) {
                change_x_velocity(200);
            } else if (d_key == true) {
                change_x_velocity(200);
            } else if (a_key == true) {
                change_x_velocity(-200);
            } else {
                change_x_velocity(0);
            }

            // Update main player x position
            float x = main.position().x + main.velocity().width * dt;

            Main next_main({x, main.position().y}, main.velocity(), main.HP(), main.invincibility(),
                           main.hitbox_active(), main.jump(), main.left_or_not());

            if (next_main.hurtbox().x >= 0 &&
                next_main.hurtbox().x + next_main.hurtbox().width <= 800) {
                main = next_main;
            }

            // Check if main player is jumping. If so, update velocity and position accordingly
            if (main.jump() == true) {
                float y = main.position().y - main.velocity().height * dt - (1 / 2) * -9.8 * dt * dt;
                Main next_main({main.position().x, y}, main.velocity(), main.HP(),
                               main.invincibility(), main.hitbox_active(),
                               main.jump(), main.left_or_not());

                // Check to see if this new position goes below the screen. If so, stop at ground. Keeps player grounded
                if (next_main.hurtbox().y + next_main.hurtbox().height > 500) {
                    make_jump(false);
                    float h = 500;
                    main = Main({main.position().x, h}, main.velocity(), main.HP(),
                                main.invincibility(), main.hitbox_active(),
                                main.jump(), main.left_or_not());
                } else {
                    main = next_main;
                    change_y_velocity(dt); // Updates velocity
                }

            }

            // If the sword has been swung by key "p", this hitbox counter will keep track of how long it has been
            // active. After half a second, it will retract the sword.
            if (main.hitbox_active() == true) {
                hitbox_counter += 1;
                if (hitbox_counter > 30) {
                    swing_retract_sword(false);
                    hitbox_counter = 0;
                }
            }

            // If Player has been invincible for more than 2 seconds, make them vulnerable again
            if (main.invincibility() == true) {
                main_inv_counter += 1;
                if (main_inv_counter >= 120) {
                    main = Main(main.position(), main.velocity(), main.HP(),
                                false, main.hitbox_active(), main.jump(),
                                main.left_or_not());
                    main_inv_counter = 0;
                }
            }

            ///
            /// Updates which rely on the Enemy state
            ///

            // spawn enemies in a fixed interval if they have not spawned
            if (counter == 300) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(600 / 3,
                                                                     500), {0, 0},
                                        30, true, false, 0));
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(289,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 2;
            } else if (counter == 600) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(101,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 1;
            } else if (counter == 900) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(450,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 1;
            } else if (counter == 1200) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(568,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 1;
            } else if (counter == 1500) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(700,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 1;
            } else if (counter == 1800) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(326,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 1;
            } else if (counter == 2100) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(278,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(103,
                                                                     500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 2;
            } else if (counter == 2400) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(675,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 1;
            } else if (counter == 2700) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(276,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(400,
                                                                     500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 2;
            } else if (counter == 3000) {
                enemies.push_back(Enemy(ge211::geometry::Posn<float>(100,
                                                 500), {0, 0},
                                        30, true, false, 0));
                enemy_counter += 1;
            }

            /// Updates for each individual enemy
            for (Enemy& enemy_: enemies) {

                // Update x_position if not frozen
                if (frozen == false) {
                    float x_en = enemy_.position().x + enemy_.velocity().width * dt;

                    Enemy next_enemy({x_en, enemy_.position().y}, enemy_.velocity(), enemy_.HP(),
                                     enemy_.invincibility(), enemy_.hitbox_active(), enemy_.inv_timer());

                    if (next_enemy.hurtbox().x >= 0 &&
                        next_enemy.hurtbox().x + next_enemy.hurtbox().width <= 800) {
                        enemy_ = next_enemy;
                    } else {
                        enemy_ = Enemy({x_en, enemy_.position().y}, {enemy_.velocity().width * -1, 0},
                                       enemy_.HP(), enemy_.invincibility(), enemy_.hitbox_active(),
                                       enemy_.inv_timer());
                    }
                }

                // Check if main hurtbox and enemy hitbox have collided
                if (main.invincibility() == false) {
                    bool hit = doOverlap(main.hurtbox().top_left(), main.hurtbox().bottom_right(),
                                         enemy_.hitbox().top_left(), enemy_.hitbox().bottom_right());
                    if (hit == true) {
                        do_damage_main(10);
                    }
                }

                // Check if enemy hurtbox and main player hitbox have collided. Do damage to enemy if so.
                if (main.left_or_not() == true && main.hitbox_active() == true) {
                    if (enemy_.invincibility() == false) {
                        bool hit = doOverlap(main.left_active_hitbox().top_left(),
                                             main.left_active_hitbox().bottom_right(),
                                             enemy_.hitbox().top_left(),
                                             enemy_.hitbox().bottom_right());
                        if (hit == true) {
                            enemy_ = do_damage_en(enemy_, 10);
                        }
                    }
                } else if ((main.left_or_not() == false && main.hitbox_active() == true)) {
                    if (enemy_.invincibility() == false) {
                        bool hit = doOverlap(main.right_active_hitbox().top_left(),
                                             main.right_active_hitbox().bottom_right(),
                                             enemy_.hitbox().top_left(),
                                             enemy_.hitbox().bottom_right());
                        if (hit == true) {
                            enemy_ = do_damage_en(enemy_, 10);
                        }
                    }
                }

                // Check if enemy's HP is equal or below 0. If so, then dead
                if (enemy_.HP() <= 0) {
                    enemy_ = Enemy({10000, 10000},{0, 0},
                                   0, 0, false, false);
                }

                // Check if they've been invincible for two seconds. Also checks if they have just
                // spawned and need to start moving. If they've been invincible and haven't been moving, they've just
                // spawned and to start moving now.
                float en_x = 0;
                if (enemy_.invincibility() == true) {
                    enemy_ = inc_inv_timer(enemy_);

                    if (enemy_.inv_timer() >= 120) {

                        if (enemy_.velocity().width == 0) {
                            en_x = -100;
                        } else {
                            en_x = enemy_.velocity().width;
                        }

                        enemy_ = Enemy(enemy_.position(), {en_x, 0}, enemy_.HP(),
                                       false, enemy_.hitbox_active(), 0);
                    }
                }
            }

            ///
            /// Updates with items
            ///

            // Spawn hearts in time intervals, but only one item of each type can spawn at a time
            if (counter/60 == 12) {
                heart = Heart({250,450,10,10});
            } else if (counter/60 == 20 && heart.detection_box().x == 1000) {
                heart = Heart({400,400,10,10});
            } else if (counter/60 == 40 && heart.detection_box().x == 1000) {
                heart = Heart({300,550,10,10});
            } else if (counter/60 == 60 && heart.detection_box().x == 1000) {
                heart = Heart({600,435,10,10});
            } else if (counter/60 == 70 && heart.detection_box().x == 1000) {
                heart = Heart({235,412,10,10});
            } else if (counter/60 == 80 && heart.detection_box().x == 1000) {
                heart = Heart({700,500,10,10});
            }

            // Spawn freezes at certain time intervals, but only one can exist at a time
            if (counter/60 == 20) {
                freeze = Freeze({50,467,10,10});
            } else if (counter/60 == 50 && freeze.detection_box().x == 1000) {
                freeze = Freeze({500, 423, 10, 10});
            }

            // Check if main character has collided with the present heart
            bool item_hit_heart = doOverlap(main.hurtbox().top_left(), main.hurtbox().bottom_right(),
                                            heart.detection_box().top_left(), heart.detection_box().bottom_right());

            if (item_hit_heart == true && main.HP() != 100) {
                do_damage_main(-10);
                heart = Heart({1000, 10000, 0, 0});
            }

            // Check if main character has collided with the present freeze
            bool item_hit_freeze = doOverlap(main.hurtbox().top_left(), main.hurtbox().bottom_right(),
                                             freeze.detection_box().top_left(), freeze.detection_box().bottom_right());

            if (item_hit_freeze == true && frozen == false) {
                frozen = true;
                freeze = Freeze({1000, 10000, 0, 0});
            }

            // Check if the enemies are currently frozen. If so, increment the freeze timer. End freeze at 6 seconds
            if (frozen == true) {
                freeze_counter += 1;
                if (freeze_counter / 60 > 6) {
                    frozen = false;
                    freeze_counter = 0;
                }
            }

            // Check if all enemies are dead and end game if so
            if (all_dead(enemies) == true) {
                over = true;
                win = true;
            }

            // Check if player's HP is equal or below 0, then game over
            if (main.HP() <= 0) {
                over = true;
                win = false;
            }
            counter += 1; // This counter keeps track of unpaused time to allow me to initiate time=specific events
        }
    }
}
