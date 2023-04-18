

#pragma once

#include "view.hxx"
#include <ge211.hxx>

struct Controller : ge211::Abstract_game
{
    //
    // CONSTRUCTOR
    //
    explicit Controller(Model&);


    //
    // MEMBER FUNCTIONS
    //

    /// Defines how the game responds to key events.
    /// The a key makes the character move left when being pressed
    /// The d key makes the character move right when being pressed
    ///  The w key makes the character jump when pressed
    /// The space bar pauses the game
    /// The p key swings the sword
    void on_key_up(ge211::Key) override;
    void on_key_down(ge211::Key) override;


    /// This function is used in the model to keep track of essentially
    // everything the model for specifics
    void on_frame(double dt) override;

    /// The initial window dimensions of the game
    ge211::Dims<int> initial_window_dimensions() const override;

    void draw(ge211::Sprite_set&) override;


    //
    // MEMBER VARIABLES
    //

    /// Reference to the model
    Model& model;

    /// Reference to the view
    View view;
};
