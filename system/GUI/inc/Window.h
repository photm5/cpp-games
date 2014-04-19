#ifndef GUARD_GUI_WINDOW
#define GUARD_GUI_WINDOW

#include <string>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "library/events/inc/Emitter.h"
#include "library/events/inc/Listener.h"

#include "Draw_event.h"

namespace GUI {

    class Window : public events::Emitter<sf::Event>, events::Emitter<Draw_event> {
        public:
            Window (sf::RenderWindow& window);

            void event_loop ();

            void set_output (events::Listener<sf::Event>& sfml_event_listener);
            void set_output (events::Listener<Draw_event>& draw_event_listener);

        private:
            sf::RenderWindow& window;

            events::Listener<sf::Event>* sfml_event_listener;
            events::Listener<Draw_event>* draw_event_listener;

    };

}

#endif // GUARD_GUI_WINDOW
