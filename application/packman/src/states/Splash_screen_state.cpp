#include "Splash_screen_state.h"

using namespace packman;

Splash_screen_state::Splash_screen_state (events::Listener<std::shared_ptr<Game_state>>* next_state_listener)
    : resource_manager(std::make_shared<GUI::Resource_manager>("application/packman/res/", ".png")), splash(resource_manager->get_texture("splash.intro"))
{
    this->next_state_listener = next_state_listener;
}

void Splash_screen_state::handle_event (sf::Event& sfml_event) {
    if (sfml_event.type == sf::Event::KeyPressed && sfml_event.key.code == sf::Keyboard::Space) {
        std::shared_ptr<Game_state> next_state = std::make_shared<Play_state> (next_state_listener, resource_manager);
        next_state_listener->handle_event(next_state);
    }
}

void Splash_screen_state::handle_event (GUI::Draw_event& draw_event) {
    draw_event.get_target().draw(splash);
}

void Splash_screen_state::begin () {
}

void Splash_screen_state::end () {
}
