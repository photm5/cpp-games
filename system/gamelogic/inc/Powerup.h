#ifndef GUARD_GAMELOGIC_POWERUP
#define GUARD_GAMELOGIC_POWERUP

#include "library/geom2d/inc/Vector.h"

#include "Entity.h"

namespace gamelogic {

    class Powerup : public Entity {
        public:
            Powerup (geom2d::Vector<int> position) : Entity(position) {};
    };

}

#endif // GUARD_GAMELOGIC_POWERUP
