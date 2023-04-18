//
// Created by ams1258 on 12/1/2022.
//

#pragma once

#include <ge211.hxx>

#include <iostream>

// Makes the class for the heart and freeze items

class Heart {

public:
    Heart(ge211::Rect<int> rect);
    ge211::Rect<int> detection_box() const;
    int healing_factor();

private:
    int Healing_Factor;
    // The area that the heart takes up, allowing the game to detect whether
    // the character has touched it
    ge211::Rect<int> detection_box_;

};

class Freeze {

public:
    Freeze(ge211::Rect<int> rect);
    ge211::Rect<int> detection_box() const;

private:
    // The area that the freeze takes up, allowing the game to detect whether
    // the character has touched it
    ge211::Rect<int> detection_box_;

};