#ifndef GUARD_GAMELOGIC_WORLD
#define GUARD_GAMELOGIC_WORLD

#include <vector>
#include <memory>
#include <algorithm>

#include "library/events/inc/Listener.h"
#include "library/events/inc/Service.h"
#include "library/events/inc/Broadcaster.h"

#include "library/geom2d/inc/Vector.h"

#include "Level.h"
#include "Powerup.h"
#include "Actor.h"

#include "Next_turn_event.h"
#include "Powerup_event.h"
#include "Actor_collision_event.h"
#include "Actor_movement_event.h"

namespace gamelogic {

    class World : public events::Listener<Actor_movement_event> {
        public:
            World (Level level);
            ~World () = default;


            void spawn_actor (std::shared_ptr<Actor> actor);
            void spawn_powerup (std::shared_ptr<Powerup> powerup);

            void kill_actor (const Actor* actor);

            void handle_event (Actor_movement_event& event);
            void next_turn ();

            events::Service<Next_turn_event>& get_turns_service ();
            events::Service<Powerup_event>& get_powerup_service ();
            events::Service<Actor_collision_event>& get_actor_collision_service ();
            events::Service<Actor_movement_event>& get_actor_movement_service ();

            const Level& get_level () const;

        private:
            Level level;
            std::vector<std::shared_ptr<Actor>> actors;
            std::vector<std::shared_ptr<Powerup>> powerups;

            events::Broadcaster<Next_turn_event> next_turn_broadcaster;
            events::Broadcaster<Powerup_event> powerup_broadcaster;
            events::Broadcaster<Actor_collision_event> actor_collision_broadcaster;
            events::Broadcaster<Actor_movement_event> actor_movement_broadcaster;

            Actor* get_actor_at (geom2d::Vector<int> position);
            Powerup* get_powerup_at (geom2d::Vector<int> position);

            bool collisions (Actor_movement_event& move);

    };

}

#endif // GUARD_GAMELOGIC_WORLD
