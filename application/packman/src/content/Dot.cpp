#include "Dot.h"

using namespace packman;

Dot::Dot (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager, gamelogic::World* world)
: sprite(resource_manager.get_texture("powerup.dot")), gamelogic::Powerup(position)
{
    sprite.setScale(2.f, 2.f);
    sprite.setPosition(32 * get_position().get_x(), 32 * get_position().get_y());
    used = false;
    this->world = world;
}

void Dot::handle_event (GUI::Draw_event& draw_event) {
    if (!used) {
        draw_event.get_target().draw(sprite);
    }
}

void Dot::handle_event (gamelogic::Powerup_event& powerup_event) {
    if (powerup_event.get_powerup() == this && powerup_event.get_actor()->has_property("actor.packman")) {
        world->kill_powerup(this);
        used = true;
    }
}

bool Dot::has_property (std::string property_name) const {
    if (property_name == "powerup.dot")
        return true;
    if (property_name == "score")
        return true;
    if (property_name == "no obstruct")
        return true;
    return false;
}

int Dot::get_property (std::string property_name) const {
    if (property_name == "score")
        return 1;
    return 0;
}
