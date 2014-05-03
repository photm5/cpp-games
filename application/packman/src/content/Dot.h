#ifndef GUARD_PACKMAN_DOT
#define GUARD_PACKMAN_DOT

#include <SFML/Graphics.hpp>

#include "system/gamelogic/inc/World.h"
#include "system/gamelogic/inc/Powerup.h"
#include "system/gamelogic/inc/Powerup_event.h"

#include "system/GUI/inc/Resource_manager.h"
#include "system/GUI/inc/Draw_event.h"

#include "library/events/inc/Listener.h"

#include "library/geom2d/inc/Vector.h"

namespace packman {

    class Dot : public gamelogic::Powerup, public events::Listener<GUI::Draw_event> {
        public:
            Dot (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager, gamelogic::World* world);
            ~Dot () = default;

            void handle_event (GUI::Draw_event& draw_event);
            void handle_event (gamelogic::Powerup_event& powerup_event);

            bool has_property (std::string property_name) const;
            int get_property (std::string property_name) const;

        private:
            sf::Sprite sprite;
            gamelogic::World* world;

            bool used;

    };

}

#endif // GUARD_PACKMAN_DOT
