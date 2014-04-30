#include "Window.h"

using namespace GUI;

Window::Window (sf::RenderWindow& window) : window(window) {
}

void Window::event_loop () {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                sfml_event_forwarder.handle_event(event);
            }
        }

        window.clear(sf::Color::Black);
        Draw_event draw_event = Draw_event(window);
        draw_event_forwarder.handle_event(draw_event);
        window.display();
    }
}

events::Emitter<sf::Event>* Window::get_sfml_emitter () {
    return &sfml_event_forwarder;
}

events::Emitter<Draw_event>* Window::get_draw_emitter () {
    return &draw_event_forwarder;
}
