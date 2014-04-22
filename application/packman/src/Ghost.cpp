#include "Ghost.h"

using namespace packman;

Ghost::Ghost (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager, gamelogic::World* world)
: gamelogic::Actor(position), sprite(resource_manager.get_texture("actor.ghost")), target_position(position)
{
    sprite.setScale(2.f, 2.f);
    update_positions();
    dead = false;
    this->world = world;
}

void Ghost::handle_event (GUI::Draw_event& draw_event) {
    if (!dead)
        draw_event.get_target().draw(sprite);
}

void Ghost::handle_event (gamelogic::Next_turn_event& next_turn_event) {
    geom2d::Vector<int> offset (0, 0);
    if (get_position().get_x() > target_position.get_x()) {
        offset += {-1, 0};
    } else if (get_position().get_x() < target_position.get_x()) {
        offset += {1, 0};
    }
    if (get_position().get_y() > target_position.get_y()) {
        offset += {0, -1};
    } else if (get_position().get_y() < target_position.get_y()) {
        offset += {0, 1};
    }
    if (offset != geom2d::Vector<int> (0, 0)) {
        geom2d::Vector<int> new_position = get_position() + offset;
        gamelogic::Actor_movement_event move (this, new_position);
        next_turn_event.get_movement_listener()->handle_event(move);
    }
}

void Ghost::handle_event (gamelogic::Powerup_event& powerup_event) {
}

void Ghost::handle_event (gamelogic::Actor_movement_event& movement_event) {
    if (movement_event.get_actor() == this) {
        set_position(movement_event.get_new_position());
        update_positions();
    } else if (movement_event.get_actor()->has_property("actor.packman")) {
        target_position = movement_event.get_new_position();
    }
}

void Ghost::handle_event (gamelogic::Actor_collision_event& collision_event) {
    if (is_eat_me_collision(collision_event)) {
        world->kill_actor(this);
        dead = true;
    }
}

bool Ghost::has_property (std::string property_name) {
    if (property_name == "eat packman")
        return true;
    if (property_name == "actor.ghost")
        return true;
    return false;
}

int Ghost::get_property (std::string property_name) {
    return 0;
}

void Ghost::update_positions () {
    sprite.setPosition(32 * get_position().get_x(), 32 * get_position().get_y());
}

bool Ghost::is_eat_me_collision (gamelogic::Actor_collision_event& collision_event) {
    return (collision_event.get_executing_actor()->has_property("eat ghost")
        || collision_event.get_target_actor()->has_property("eat ghost"))
        && (collision_event.get_executing_actor() == this
        || collision_event.get_target_actor() == this);
}
