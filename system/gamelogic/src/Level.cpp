#include "Level.h"

using namespace gamelogic;

Tile* Level::get_tile_at (geom2d::Vector<int> position) {
    auto at = std::find_if (tiles.begin(), tiles.end(),
            [&](std::shared_ptr<Tile> t){return t->get_position() == position;});
    if (at == tiles.end())
        return nullptr;
    return at->get();
}

void Level::set_tile (std::shared_ptr<Tile> tile) {
    remove_tile_at(tile->get_position());
    tiles.push_back(tile);
}

void Level::remove_tile_at (geom2d::Vector<int> position) {
    tiles.erase(std::remove_if(tiles.begin(), tiles.end(),
                [&](std::shared_ptr<Tile> t){return t->get_position() == position;}), tiles.end());
}
