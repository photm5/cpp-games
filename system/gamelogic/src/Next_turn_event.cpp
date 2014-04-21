#include "Next_turn_event.h"

using namespace gamelogic;

Next_turn_event::Next_turn_event (events::Listener<Actor_movement_event>* movement_listener) {
    this->movement_listener = movement_listener;
}

events::Listener<Actor_movement_event>* Next_turn_event::get_movement_listener () {
    return movement_listener;
}
