#include "Window.h"

using namespace GUI;

Window::Window (sf::RenderWindow& window) : window(window) {
    sfml_event_listener = nullptr;
    draw_event_listener = nullptr;
}

void Window::event_loop () {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                sfml_event_listener->handle_event(event);
            }
        }

        window.clear(sf::Color::Black);
        Draw_event draw_event = Draw_event(window);
        draw_event_listener->handle_event(draw_event);
        window.display();
    }
}

void Window::set_output (events::Listener<sf::Event>& sfml_event_listener) {
    this->sfml_event_listener = &sfml_event_listener;
}

void Window::set_output (events::Listener<Draw_event>& draw_event_listener) {
    this->draw_event_listener = &draw_event_listener;
}
