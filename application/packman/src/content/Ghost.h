#ifndef GUARD_PACKMAN_GHOST
#define GUARD_PACKMAN_GHOST

#include "system/gamelogic/inc/Actor.h"
#include "system/gamelogic/inc/Powerup.h"
#include "system/gamelogic/inc/World.h"

#include "system/GUI/inc/Resource_manager.h"
#include "system/GUI/inc/Draw_event.h"

#include "library/events/inc/Listener.h"

#include "library/geom2d/inc/Vector.h"

namespace packman {

    class Ghost : public gamelogic::Actor, public events::Listener<GUI::Draw_event> {
        public:
            Ghost (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager, gamelogic::World* world);
            ~Ghost () = default;

            void handle_event (GUI::Draw_event& draw_event);

            void handle_event (gamelogic::Next_turn_event& next_turn_event);
            void handle_event (gamelogic::Powerup_event& powerup_event);
            void handle_event (gamelogic::Actor_movement_event& movement_event);
            void handle_event (gamelogic::Actor_collision_event& collision_event);

            bool has_property (std::string property_name);
            int get_property (std::string property_name);

        private:
            sf::Sprite sprite;
            geom2d::Vector<int> target_position;
            gamelogic::World* world;

            bool dead;

            void update_positions ();
            bool is_eat_me_collision (gamelogic::Actor_collision_event& collision_event);
    };

}

#endif // GUARD_PACKMAN_GHOST
