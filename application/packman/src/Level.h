#ifndef GUARD_PACKMAN_LEVELS
#define GUARD_PACKMAN_LEVELS

#include "system/gamelogic/inc/World.h"
#include "system/gamelogic/inc/Level.h"

#include "system/GUI/inc/Draw_event.h"

#include "content/Packman.h"
#include "content/Ghost.h"
#include "content/Dot.h"
#include "content/Eat_ghost_powerup.h"
#include "content/Wall.h"

#include "library/events/inc/Shared_broadcaster.h"

#include <string>
#include <memory>
#include <iostream>
#include <fstream>

namespace packman {

    class Level {
        public:
            Level (std::string name, GUI::Resource_manager* resource_manager);
            ~Level () = default;

            void reset ();

            std::shared_ptr<gamelogic::World> get_world ();
            events::Shared_broadcaster<GUI::Draw_event> get_draw_broadcaster ();

            events::Emitter<Score_change_event>* get_scorechange_emitter ();
            events::Emitter<Eattimer_change_event>* get_eattimer_emitter ();

        private:
            std::string name;

            std::shared_ptr<gamelogic::World> world;
            events::Shared_broadcaster<GUI::Draw_event> draw_broadcaster;
            GUI::Resource_manager* resource_manager;

            events::Emitter<Score_change_event>* score_emitter;
            events::Emitter<Eattimer_change_event>* eattimer_emitter;

    };

}

#endif // GUARD_PACKMAN_LEVELS
