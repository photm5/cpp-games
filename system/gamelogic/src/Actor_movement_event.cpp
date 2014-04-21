#include "Actor_movement_event.h"

using namespace gamelogic;

Actor_movement_event::Actor_movement_event (Actor* actor, geom2d::Vector<int> new_position)
: actor(actor), new_position(new_position) {
}

Actor* Actor_movement_event::get_actor () const {
    return actor;
}
geom2d::Vector<int> Actor_movement_event::get_new_position () const {
    return new_position;
}
