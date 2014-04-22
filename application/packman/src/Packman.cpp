#include "Packman.h"

using namespace packman;

Packman::Packman (geom2d::Vector<int> position, GUI::Resource_manager& resource_manager, gamelogic::World* world)
: sprite(resource_manager.get_texture("actor.packman")), gamelogic::Actor(position)
{
    sprite.setScale(2.f, 2.f);
    score = 0;
    eat_ghosts = 0;
    update_positions();
    this->world = world;
    dead = false;
}

void Packman::handle_event (GUI::Draw_event& draw_event) {
    if (!dead)
        draw_event.get_target().draw(sprite);
}

void Packman::handle_event (gamelogic::Next_turn_event& next_turn_event) {
    if (eat_ghosts > 0) {
        --eat_ghosts;
    }

    geom2d::Vector<int> offset (0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        offset += { -1, 0 };
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        offset += { 1, 0 };
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        offset += { 0, 1 };
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        offset += { 0, -1 };
    }
    if (offset != geom2d::Vector<int> (0,0)) {
        geom2d::Vector<int> new_position = get_position() + offset;
        gamelogic::Actor_movement_event move (this, new_position);
        next_turn_event.get_movement_listener()->handle_event(move);
    }
}

void Packman::handle_event (gamelogic::Powerup_event& powerup_event) {
    if (powerup_event.get_actor() == this) {
        std::cout << "powerup!!" << std::endl;
        if (powerup_event.get_powerup()->has_property("score")) {
            score += powerup_event.get_powerup()->get_property("score");
        }
        if (powerup_event.get_powerup()->has_property("eat ghost")) {
            eat_ghosts += powerup_event.get_powerup()->get_property("eat ghost");
        }
    }
}

void Packman::handle_event (gamelogic::Actor_movement_event& movement_event) {
    if (movement_event.get_actor() == this) {
        set_position(movement_event.get_new_position());
        update_positions();
    }
}

void Packman::handle_event (gamelogic::Actor_collision_event& collision_event) {
    if (is_ghost_me_collision(collision_event)) {
        if (has_property("eat ghost")) {
            score += 50;
        } else {
            world->kill_actor(this);
            dead = true;
        }
    }
}

// properties

bool Packman::has_property (std::string property_name) {
    if (property_name == "score")
        return true;
    if (property_name == "actor.packman")
        return true;
    if (property_name == "eat ghost")
        return eat_ghosts > 0;
    return false;
}

int Packman::get_property (std::string property_name) {
    if (property_name == "score")
        return score;
    return 0;
}


// private memberfunctions

void Packman::update_positions () {
    sprite.setPosition(32 * get_position().get_x(), 32 * get_position().get_y());
}

bool Packman::is_ghost_me_collision (gamelogic::Actor_collision_event& collision_event) {
    return (collision_event.get_executing_actor() == this
                || collision_event.get_target_actor() == this)
        && (collision_event.get_executing_actor()->has_property("eat packman")
                || collision_event.get_target_actor()->has_property("eat packman"));
}
