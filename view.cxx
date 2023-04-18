// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "view.hxx"
#include "model.hxx"
#include <string>

///
/// VIEW CONSTANTS
///
static ge211::Color const main_color {217, 175, 55};
static ge211::Color const enemy_color {128, 0, 32, 100};
static ge211::Color const enemy_inv_color {128, 0, 32, 255};
static ge211::Color const main_inv_color {217, 175, 55, 80};
static ge211::Color const sword_color {196, 202, 206};
static ge211::Color const heart_color {255, 0, 0};
static ge211::Color const freeze_color {150, 150, 255};


///
/// VIEW CONSTRUCTOR
///

View::View(Model const& m)
        : model(m),
          main_sprite({model.main.hurtbox().width,model.main.hurtbox().height}, main_color),
          main_inv_sprite({model.main.hurtbox().width,model.main.hurtbox().height}, main_inv_color),
          enemy_sprite({model.main.hurtbox().width,model.main.hurtbox().height}, enemy_color),
          enemy_inv_sprite({model.main.hurtbox().width,model.main.hurtbox().height}, enemy_inv_color),
          sword_retracted_sprite({model.main.right_inactive_hitbox().width,
                                  model.main.right_inactive_hitbox().height}, sword_color),
          sword_swung_sprite({model.main.right_active_hitbox().width,
                              model.main.right_active_hitbox().height}, sword_color),
          heart_sprite(5, heart_color),
          freeze_sprite(5, freeze_color)

{ }

///
/// VIEW FUNCTIONS
///

int view_counter = 0;

void
View::draw(ge211::Sprite_set& sprites)
{
    // main character

    if (model.main.invincibility() == true) {
        if (view_counter % 3 == 0) {
            sprites.add_sprite(main_sprite, {model.main.hurtbox().x, model.main.hurtbox().y}, 0);
        } else {
            sprites.add_sprite(main_inv_sprite, {model.main.hurtbox().x, model.main.hurtbox().y}, 0);
        }
    } else {
        sprites.add_sprite(main_sprite, {model.main.hurtbox().x, model.main.hurtbox().y}, 0);
    }
    // main character HP
    std::string s = std::to_string(model.main.HP());
    HP_text = ge211::Text_sprite("HP " + s + "/100", {"sans.ttf", 15});
    sprites.add_sprite(HP_text, {100,100}, 30);

    // pause text
    if (model.paused == true) {
        paused_text = ge211::Text_sprite("Paused", {"sans.ttf", 30});
        sprites.add_sprite(paused_text, {550, 250}, 30);
    }

    // Animate the sword depending on which way the character is facing and if it's swung or not
    if (model.main.hitbox_active() == true) {

        if (model.main.left_or_not() == true) {
            sprites.add_sprite(sword_swung_sprite, {model.main.left_active_hitbox().x,
                                                    model.main.left_active_hitbox().y}, 1);
        } else {
            sprites.add_sprite(sword_swung_sprite, {model.main.right_active_hitbox().x,
                                                    model.main.right_active_hitbox().y}, 1);
        }
    } else {

        if (model.main.left_or_not() == true) {
            sprites.add_sprite(sword_retracted_sprite, {model.main.left_inactive_hitbox().x,
                                                        model.main.left_inactive_hitbox().y}, 1);
        } else {
            sprites.add_sprite(sword_retracted_sprite, {model.main.right_inactive_hitbox().x,
                                                        model.main.right_inactive_hitbox().y}, 1);
        }
    }

    // Draw the enemy sprites.
    for (auto enemy_ : model.enemies) {
        if (enemy_.invincibility() == true) {
            if (view_counter % 3 == 0) {
                sprites.add_sprite(enemy_sprite, {enemy_.hurtbox().x, enemy_.hurtbox().y}, 0);
            } else {
                sprites.add_sprite(enemy_inv_sprite, {enemy_.hurtbox().x, enemy_.hurtbox().y}, 0);
            }
        } else {
            sprites.add_sprite(enemy_sprite, {enemy_.hurtbox().x, enemy_.hurtbox().y}, 0);
        }
    }

    // Display win or lose text when the game is over
    if (model.over == true) {
        if (model.win == false) {
            final_text = ge211::Text_sprite("Game Over, You Lost", {"sans.ttf", 30});
            sprites.add_sprite(final_text, {250, 250}, 30);
        } else {
            final_text = ge211::Text_sprite("You win!", {"sans.ttf", 30});
            sprites.add_sprite(final_text, {300, 250}, 30);
        }
    }

    // Draw items
    sprites.add_sprite(heart_sprite, model.heart.detection_box().top_left(), 30);
    sprites.add_sprite(freeze_sprite, model.freeze.detection_box().top_left(), 30);


    view_counter += 1;


}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return {800,500};
}

