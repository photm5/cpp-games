#include "Eat_ghost_powerup.h"

using namespace packman;

Eat_ghost_powerup::Eat_ghost_powerup (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager, gamelogic::World* world)
: sprite(resource_manager.get_texture("powerup.eat-ghost")), gamelogic::Powerup(position)
{
    sprite.setScale(2.f, 2.f);
    sprite.setPosition(32 * get_position().get_x(), 32 * get_position().get_y());
    used = false;
    this->world = world;
}

void Eat_ghost_powerup::handle_event (GUI::Draw_event& draw_event) {
    if (!used) {
        draw_event.get_target().draw(sprite);
    }
}

void Eat_ghost_powerup::handle_event (gamelogic::Powerup_event& powerup_event) {
    if (powerup_event.get_powerup() == this && powerup_event.get_actor()->has_property("actor.packman")) {
        world->kill_powerup(this);
        used = true;
    }
}

bool Eat_ghost_powerup::has_property (std::string property_name) const {
    if (property_name == "powerup.eat-ghost")
        return true;
    if (property_name == "eat ghost")
        return true;
    if (property_name == "no obstruct")
        return true;
    return false;
}

int Eat_ghost_powerup::get_property (std::string property_name) const {
    if (property_name == "eat ghost")
        return 50;
    return 0;
}
