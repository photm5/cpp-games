#include <chrono>
#include <cstdlib>
#include <vector>

#include <SFML/Graphics.hpp>

#include "states/Game_state.h"
#include "states/Splash_screen_state.h"

#include "system/GUI/inc/Draw_event.h"
#include "system/GUI/inc/Window.h"

#include "library/events/inc/Listener.h"
#include "library/events/inc/Forwarder.h"
#include "library/events/inc/Broadcaster.h"

struct State_manager : events::Listener<std::shared_ptr<packman::Game_state>> {

    void handle_event (std::shared_ptr<packman::Game_state>& next_state) {
        draw_event_forwarder.set_output(nullptr);
        sfml_event_forwarder.set_output(nullptr);
        if (current_state.get() != nullptr) {
            current_state->end();
        }
        current_state = next_state;
        current_state->begin();
        draw_event_forwarder.set_output(current_state.get());
        sfml_event_forwarder.set_output(current_state.get());
    };

    events::Listener<GUI::Draw_event>* get_draw_listener () {
        return &draw_event_forwarder;
    };

    events::Listener<sf::Event>* get_sfml_listener () {
        return &sfml_event_forwarder;
    };

    events::Forwarder<GUI::Draw_event> draw_event_forwarder;
    events::Forwarder<sf::Event> sfml_event_forwarder;

    std::shared_ptr<packman::Game_state> current_state;
};

int main(int argc, char *argv[])
{

    std::srand(std::chrono::system_clock::now().time_since_epoch().count());

    State_manager state_manager;

    std::shared_ptr<packman::Game_state> first_state = std::make_shared<packman::Splash_screen_state> (&state_manager);
    state_manager.handle_event(first_state);

    sf::RenderWindow sfwindow(sf::VideoMode(1280,1024), "Packman");
    GUI::Window window(sfwindow);

    window.get_sfml_emitter()->set_output(state_manager.get_sfml_listener());
    window.get_draw_emitter()->set_output(state_manager.get_draw_listener());

    window.event_loop();

    return 0;
}
