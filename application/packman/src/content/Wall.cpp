#include "Wall.h"

using namespace packman;

Wall::Wall (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager)
    : sprite(resource_manager.get_texture("tile.wall")), gamelogic::Tile(position)
{
    sprite.setScale(2, 2);
    sprite.setPosition(get_position().get_x() * 32, get_position().get_y() * 32);
}


void Wall::handle_event (GUI::Draw_event& draw_event) {
    draw_event.get_target().draw(sprite);
}


bool Wall::has_property (std::string property_name) {
    return false;
}

int Wall::get_property (std::string property_name) {
    return 0;
}
