#ifndef GUARD_PACKMAN_PACKMAN
#define GUARD_PACKMAN_PACKMAN

#include <SFML/Window.hpp>

#include "system/gamelogic/inc/World.h"

#include "system/gamelogic/inc/Actor.h"
#include "system/gamelogic/inc/Powerup.h"

#include "system/gamelogic/inc/Next_turn_event.h"
#include "system/gamelogic/inc/Powerup_event.h"
#include "system/gamelogic/inc/Actor_movement_event.h"
#include "system/gamelogic/inc/Actor_collision_event.h"

#include "system/GUI/inc/Resource_manager.h"
#include "system/GUI/inc/Draw_event.h"

#include "library/geom2d/inc/Vector.h"

#include "library/events/inc/Listener.h"
#include "library/events/inc/Forwarder.h"
#include "library/events/inc/Emitter.h"

namespace packman {

    class Packman;

    struct Score_change_event {
        int new_score;
        Packman* packman;
    };

    struct Eattimer_change_event {
        int new_time;
        Packman* packman;
    };

    struct Key_event_handler : events::Listener<sf::Event> {
        geom2d::Vector<int> offset = { 0, 0 };

        void handle_event (sf::Event& sfml_event) {
            geom2d::Vector<int> dir = { 0, 0 };
            switch (sfml_event.key.code) {
                case sf::Keyboard::W:
                    dir += { 0, -1 };
                    break;
                case sf::Keyboard::A:
                    dir += { -1, 0 };
                    break;
                case sf::Keyboard::S:
                    dir += { 0, 1 };
                    break;
                case sf::Keyboard::D:
                    dir += { 1, 0 };
                    break;
            }
            if (sfml_event.type == sf::Event::KeyReleased)
                dir *= { -1, -1 };
            else if (sfml_event.type != sf::Event::KeyPressed)
                return;
            using std::max;
            using std::min;
            offset = { min(1, max(-1, offset.get_x() + dir.get_x())), min(1, max(-1, offset.get_y() + dir.get_y())) };
        };
    };

    class Packman : public gamelogic::Actor, public events::Listener<GUI::Draw_event> {
        public:
            Packman (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager, gamelogic::World* world);
            ~Packman () = default;

            void handle_event (GUI::Draw_event& draw_event);

            void handle_event (gamelogic::Next_turn_event& next_turn_event);
            void handle_event (gamelogic::Powerup_event& powerup_event);
            void handle_event (gamelogic::Actor_movement_event& movement_event);
            void handle_event (gamelogic::Actor_collision_event& collision_event);

            events::Emitter<Score_change_event>* get_score_emitter ();
            events::Emitter<Eattimer_change_event>* get_eattimer_emitter ();
            events::Listener<sf::Event>* get_key_listener ();

            bool has_property (std::string property_name) const;
            int get_property (std::string property_name) const;

        private:
            gamelogic::World* world;
            sf::Sprite sprite;
            Key_event_handler key_handler;

            events::Forwarder<Score_change_event> score_forwarder;
            events::Forwarder<Eattimer_change_event> eattimer_forwarder;

            int score;
            int eat_ghosts;
            bool dead;

            void update_positions ();
            bool is_ghost_me_collision (gamelogic::Actor_collision_event& collision_event);
    };
}

#endif // GUARD_PACKMAN_PACKMAN
