#include "Entity.h"

using namespace gamelogic;

Entity::Entity (geom2d::Vector<int> pos) : position(pos) {
}

bool Entity::operator== (const Entity& other) {
    return position == other.get_position();
}

geom2d::Vector<int> Entity::get_position() const {
    return position;
}

void Entity::set_position(geom2d::Vector<int> pos) {
    position = pos;
}

bool Entity::has_property (std::string property_name) const {
    return false;
}

int Entity::get_property (std::string property_name) const {
    return 0;
}
