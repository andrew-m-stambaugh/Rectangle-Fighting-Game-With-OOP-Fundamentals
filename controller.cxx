
#include "controller.hxx"
#include "model.hxx"

Controller::Controller(Model& model)
        : model(model),
          view(model)
{ }

///
/// CONTROLLER FUNCTIONS
///

void
Controller::on_key_down(ge211::Key key)
{
    if (key == ge211::Key::code('d')) {
        model.d_pressed(true);
    }

    if (key == ge211::Key::code('a')) {
        model.a_pressed(true);
    }

    if (key == ge211::Key::code('w')) {
        model.make_jump(true);
    }

    if (key == ge211::Key::code('p')) {
        model.swing_retract_sword(true);
    }

    if (key == ge211::Key::code(' ')) {
        model.pause();
    }
}

void
Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::code('d')) {
        model.d_pressed(false);
    }

    if (key == ge211::Key::code('a')) {
        model.a_pressed(false);
    }

}
void
Controller::on_frame(double dt)
{
    model.on_frame(dt);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view.draw(sprites);
}
