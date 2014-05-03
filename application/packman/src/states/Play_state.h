#ifndef GUARD_PACKMAN_PLAY_STATE
#define GUARD_PACKMAN_PLAY_STATE

#include "Game_state.h"
#include "../Level.h"

#include <SFML/Window.hpp>

#include "system/GUI/inc/Draw_event.h"
#include "system/GUI/inc/Resource_manager.h"

#include "system/gamelogic/inc/World.h"

#include "library/events/inc/Shared_broadcaster.h"
#include "library/events/inc/Listener.h"

#include <sstream>
#include <memory>

namespace packman {

    struct Score_display : events::Listener<Score_change_event>, events::Listener<GUI::Draw_event> {
        sf::Text display;
        Score_display (sf::Font& font) {
            display.setFont(font);
            display.setString("Score");
            display.setColor(sf::Color::Green);
            display.setCharacterSize(32);
        }

        void handle_event (Score_change_event& event) {
            std::stringstream stringstream;
            stringstream << "Score: " << event.new_score;
            std::string s = stringstream.str();
            display.setString(s);
        }

        void handle_event (GUI::Draw_event& event) {
            event.get_target().draw(display);
        }
    };

    struct Eattimer_display : events::Listener<Eattimer_change_event>, events::Listener<GUI::Draw_event> {
        sf::Text display;
        Eattimer_display (sf::Font& font) {
            display.setFont(font);
            display.setString("Eattimer");
            display.setColor(sf::Color::Red);
            display.setPosition(200, 0);
            display.setCharacterSize(32);
        }

        void handle_event (Eattimer_change_event& event) {
            std::stringstream stringstream;
            stringstream << "Eat ghosts: " << event.new_time;
            std::string s = stringstream.str();
            display.setString(s);
        }

        void handle_event (GUI::Draw_event& event) {
            event.get_target().draw(display);
        }
    };

    class Play_state : public Game_state {
        public:
            Play_state (events::Listener<std::shared_ptr<Game_state>>* next_state_listener,
                    std::shared_ptr<GUI::Resource_manager> resource_manager);
            ~Play_state () = default;

            void handle_event (sf::Event& sfml_event);
            void handle_event (GUI::Draw_event& draw_event);

            void begin ();
            void end ();

        private:
            events::Listener<std::shared_ptr<Game_state>>* next_state_listener;
            std::shared_ptr<GUI::Resource_manager> resource_manager;

            events::Shared_broadcaster<GUI::Draw_event> draw_broadcaster;
            std::shared_ptr<gamelogic::World> world;

            Score_display score_listener;
            Eattimer_display eattimer_listener;

    };

}

#endif // GUARD_PACKMAN_PLAY_STATE
