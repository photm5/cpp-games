#ifndef GUARD_GAMELOGIC_POWERUP_EVENT
#define GUARD_GAMELOGIC_POWERUP_EVENT

//#include "Actor.h"
//#include "Powerup.h"

namespace gamelogic {
    class Actor;
    class Powerup;

    class Powerup_event { // Collision between an actor and a powerup
        public:
            Powerup_event (Actor* actor, Powerup* powerup);

            Actor* get_actor () const;
            Powerup* get_powerup () const;

        private:
            Actor* actor;
            Powerup* powerup;
    };
}

#endif // GUARD_GAMELOGIC_POWERUP_EVENT
