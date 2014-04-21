#ifndef GUARD_GAMELOGIC_NEXT_TURN_EVENT
#define GUARD_GAMELOGIC_NEXT_TURN_EVENT

#include "Actor_movement_event.h"

#include "library/events/inc/Listener.h"

namespace gamelogic {

    class Next_turn_event {
        public:
            Next_turn_event (events::Listener<Actor_movement_event>* movement_listener);
            ~Next_turn_event () = default;

            events::Listener<Actor_movement_event>* get_movement_listener ();

        private:
            events::Listener<Actor_movement_event>* movement_listener;
    };

}

#endif // GUARD_GAMELOGIC_NEXT_TURN_EVENT
