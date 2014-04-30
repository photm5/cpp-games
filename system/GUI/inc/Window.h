#ifndef GUARD_GUI_WINDOW
#define GUARD_GUI_WINDOW

#include <string>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "library/events/inc/Emitter.h"
#include "library/events/inc/Forwarder.h"

#include "Draw_event.h"

namespace GUI {

    class Window {
        public:
            Window (sf::RenderWindow& window);

            void event_loop ();

            events::Emitter<sf::Event>* get_sfml_emitter ();
            events::Emitter<Draw_event>* get_draw_emitter ();

        private:
            sf::RenderWindow& window;

            events::Forwarder<sf::Event> sfml_event_forwarder;
            events::Forwarder<Draw_event> draw_event_forwarder;

    };

}

#endif // GUARD_GUI_WINDOW
