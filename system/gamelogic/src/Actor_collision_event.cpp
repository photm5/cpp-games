#include "Actor_collision_event.h"

using namespace gamelogic;

Actor_collision_event::Actor_collision_event (Actor* executing, Actor* target)
: executing(executing), target(target) {
}

Actor* Actor_collision_event::get_executing_actor () const {
    return executing;
}


Actor* Actor_collision_event::get_target_actor () const {
    return target;
}
