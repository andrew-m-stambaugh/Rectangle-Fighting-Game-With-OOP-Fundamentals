

#pragma once

#include <ge211.hxx>

struct Model;

struct View
{
    //
    // CONSTRUCTOR
    //

    /// Constructs the view of the model and creates all of the sprites
    explicit View(Model const&);

    //
    // MEMBER FUNCTIONS
    //

    /// Returns game screen dimensions
    ge211::Dims<int> initial_window_dimensions() const;

    /// Draws all the entities in the model
    void draw(ge211::Sprite_set&);


    //
    // MEMBER VARIABLES
    //

    /// reference to model
    Model const& model;

    // The sprites to be used in the game
    ge211::Rectangle_sprite const main_sprite;
    ge211::Rectangle_sprite const main_inv_sprite;
    ge211::Rectangle_sprite const enemy_sprite;
    ge211::Rectangle_sprite const enemy_inv_sprite;
    ge211::Rectangle_sprite const sword_retracted_sprite;
    ge211::Rectangle_sprite const sword_swung_sprite;
    ge211::Circle_sprite const heart_sprite;
    ge211::Circle_sprite const freeze_sprite;
    ge211::Text_sprite HP_text;
    ge211::Text_sprite paused_text;
    ge211::Text_sprite final_text;
};
