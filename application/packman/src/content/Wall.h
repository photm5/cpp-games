#ifndef GUARD_PACKMAN_WALL
#define GUARD_PACKMAN_WALL

#include <SFML/Graphics.hpp>

#include "system/gamelogic/inc/Tile.h"

#include "system/GUI/inc/Resource_manager.h"
#include "system/GUI/inc/Draw_event.h"

#include "library/events/inc/Listener.h"

#include "library/geom2d/inc/Vector.h"

namespace packman {

    class Wall : public gamelogic::Tile, public events::Listener<GUI::Draw_event> {
        public:
            Wall (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager);
            ~Wall () = default;

            void handle_event (GUI::Draw_event& draw_event);

            bool has_property (std::string property_name);
            int get_property (std::string property_name);

        private:
            sf::Sprite sprite;

    };

}

#endif // GUARD_PACKMAN_WALL
