#ifndef GUARD_GAMELOGIC_LEVEL
#define GUARD_GAMELOGIC_LEVEL

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#include "library/geom2d/inc/Vector.h"

#include "Tile.h"

namespace gamelogic {

    class Level {
        public:
            Level () = default;
            ~Level () = default;

            void set_tile (std::shared_ptr<Tile> tile);

            Tile* get_tile_at (geom2d::Vector<int> position);

        private:
            std::vector<std::shared_ptr<Tile>> tiles;

            void remove_tile_at (geom2d::Vector<int> position);

    };

}

#endif // GUARD_GAMELOGIC_LEVEL
