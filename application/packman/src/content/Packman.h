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

            bool has_property (std::string property_name) const;
            int get_property (std::string property_name) const;

        private:
            gamelogic::World* world;
            sf::Sprite sprite;

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
