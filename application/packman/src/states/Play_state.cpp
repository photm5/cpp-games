#include "Play_state.h" 

using namespace packman;

Play_state::Play_state (events::Listener<std::shared_ptr<Game_state>>* next_state_listener,
        std::shared_ptr<GUI::Resource_manager> resource_manager)
    : score_listener(resource_manager->get_font ("font.dejavu")), eattimer_listener(resource_manager->get_font("font.dejavu"))
{
    this->next_state_listener = next_state_listener;
    this->resource_manager = resource_manager;
}

void Play_state::handle_event (sf::Event& sfml_event) {
    switch (sfml_event.type) {
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            key_event_listener->handle_event(sfml_event);
    }
    if (sfml_event.type == sf::Event::KeyPressed) {
        switch (sfml_event.key.code) {
            case sf::Keyboard::W:
            case sf::Keyboard::A:
            case sf::Keyboard::S:
            case sf::Keyboard::D:
                world->next_turn();
        }
    }
}

void Play_state::handle_event (GUI::Draw_event& draw_event) {
    draw_broadcaster.handle_event(draw_event);
    score_listener.handle_event(draw_event);
    eattimer_listener.handle_event(draw_event);
}


void Play_state::begin () {
    Level level ("example", resource_manager.get());

    world = level.get_world();
    draw_broadcaster = level.get_draw_broadcaster();

    level.get_player()->get_score_emitter()->set_output(&score_listener);
    level.get_player()->get_eattimer_emitter()->set_output(&eattimer_listener);
    key_event_listener = level.get_player()->get_key_listener();
}

void Play_state::end () {
}
