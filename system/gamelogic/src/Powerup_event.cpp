#include "Powerup_event.h"

using namespace gamelogic;

Powerup_event::Powerup_event (Actor* actor, Powerup* powerup)
: actor(actor), powerup(powerup) { 
}

Actor* Powerup_event::get_actor () const {
    return actor;
}

Powerup* Powerup_event::get_powerup () const {
    return powerup;
}
