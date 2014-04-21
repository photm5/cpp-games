#ifndef GUARD_GAMELOGIC_ACTOR_MOVEMENT_EVENT
#define GUARD_GAMELOGIC_ACTOR_MOVEMENT_EVENT

#include "library/geom2d/inc/Vector.h"

namespace gamelogic {
    class Actor;

    class Actor_movement_event {
        public:
            Actor_movement_event (Actor* actor, geom2d::Vector<int> new_position);

            Actor* get_actor () const;
            geom2d::Vector<int> get_new_position () const;

        private:
            Actor* actor;
            geom2d::Vector<int> new_position;

    };

}

#endif // GUARD_GAMELOGIC_ACTOR_MOVEMENT_EVENT
