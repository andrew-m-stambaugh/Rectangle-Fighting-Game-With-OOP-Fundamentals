/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "Items.hxx"
#include <algorithm>

using namespace ge211;

ge211::Rect<int>
Heart::detection_box() const
{
    return detection_box_;
}

Heart::Heart(ge211::Rect<int> rect)
        : Healing_Factor(10),
          detection_box_(rect)
{}

int
Heart::healing_factor()
{
    return Healing_Factor;
}

Freeze::Freeze(ge211::Rect<int> rect)
        : detection_box_(rect)
{}

ge211::Rect<int>
Freeze::detection_box() const
{
    return detection_box_;
}