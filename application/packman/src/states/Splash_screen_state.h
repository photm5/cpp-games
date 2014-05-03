#ifndef GUARD_PACKMAN_SPLASH_SCREEN_STATE
#define GUARD_PACKMAN_SPLASH_SCREEN_STATE

#include "Game_state.h"
#include "Play_state.h"

#include <SFML/Window.hpp>

#include "system/GUI/inc/Draw_event.h"
#include "system/GUI/inc/Resource_manager.h"

#include "library/events/inc/Listener.h"

#include <memory>

namespace packman {

    class Splash_screen_state : public Game_state {
        public:
            Splash_screen_state (events::Listener<std::shared_ptr<Game_state>>* next_state_listener);
            ~Splash_screen_state () = default;

            void handle_event (sf::Event& sfml_event);
            void handle_event (GUI::Draw_event& draw_event);

            void begin ();
            void end ();

        private:
            std::shared_ptr<GUI::Resource_manager> resource_manager;
            sf::Sprite splash;
            events::Listener<std::shared_ptr<Game_state>>* next_state_listener;

    };

}

#endif // GUARD_PACKMAN_SPLASH_SCREEN_STATE
