#ifndef GUARD_GAMELOGIC_ACTOR
#define GUARD_GAMELOGIC_ACTOR

#include "library/events/inc/Listener.h"

#include "library/geom2d/inc/Vector.h"

#include "Entity.h"
#include "Next_turn_event.h"
#include "Actor_collision_event.h"
#include "Actor_movement_event.h"

namespace gamelogic {

    class Actor :
        public Entity,
        public events::Listener<Next_turn_event>,
        public events::Listener<Actor_collision_event>,
        public events::Listener<Actor_movement_event>
    {
        public:
            Actor (geom2d::Vector<int> position) : Entity(position) {};
            virtual ~Actor () = default;
    };
}

#endif // GUARD_GAMELOGIC_ACTOR
