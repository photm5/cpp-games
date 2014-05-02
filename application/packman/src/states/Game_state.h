#ifndef GUARD_PACKMAN_GAME_STATE
#define GUARD_PACKMAN_GAME_STATE

#include <SFML/Window.hpp>

#include "system/GUI/inc/Draw_event.h"

#include "library/events/inc/Listener.h"

namespace packman {

    class Game_state
        : public events::Listener<GUI::Draw_event>,
        public events::Listener<sf::Event>
    {
        public:
            virtual void begin () = 0;
            virtual void end () = 0;
    };

}

#endif // GUARD_PACKMAN_GAME_STATE
