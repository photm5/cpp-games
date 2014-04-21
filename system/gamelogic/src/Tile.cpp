#include "Tile.h"

using namespace gamelogic;

Tile::Tile (geom2d::Vector<int> pos) : position(pos) {
}

geom2d::Vector<int> Tile::get_position () const {
    return position;
}
