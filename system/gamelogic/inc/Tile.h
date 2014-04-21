#ifndef GUARD_GAMELOGIC_TILE
#define GUARD_GAMELOGIC_TILE

#include "library/geom2d/inc/Vector.h"

namespace gamelogic {

    class Tile {
        public:
            Tile (geom2d::Vector<int> pos);

            geom2d::Vector<int> get_position () const;

        protected:
            geom2d::Vector<int> position;

    };

}

#endif // GUARD_GAMELOGIC_TILE
