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
        Eattimer_change_event e { eat_ghosts, this };
        eattimer_forwarder.handle_event(e);
    }

    geom2d::Vector<int> offset = key_handler.offset;
    if (offset != geom2d::Vector<int> (0,0)) {
        geom2d::Vector<int> new_position = get_position() + offset;
        gamelogic::Actor_movement_event move (this, new_position);
        next_turn_event.get_movement_listener()->handle_event(move);
    }
}

void Packman::handle_event (gamelogic::Powerup_event& powerup_event) {
    if (powerup_event.get_actor() == this) {
        if (powerup_event.get_powerup()->has_property("score")) {
            score += powerup_event.get_powerup()->get_property("score");
            Score_change_event s { score, this };
            score_forwarder.handle_event(s);
        }
        if (powerup_event.get_powerup()->has_property("eat ghost")) {
            eat_ghosts += powerup_event.get_powerup()->get_property("eat ghost");
            Eattimer_change_event e { eat_ghosts, this };
            eattimer_forwarder.handle_event(e);
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
            Score_change_event s { score, this };
            score_forwarder.handle_event(s);
        } else {
            world->kill_actor(this);
            dead = true;
        }
    }
}

// event services / emitters

events::Emitter<Score_change_event>* Packman::get_score_emitter () {
    return &score_forwarder;
}

events::Emitter<Eattimer_change_event>* Packman::get_eattimer_emitter () {
    return &eattimer_forwarder;
}

events::Listener<sf::Event>* Packman::get_key_listener () {
    return &key_handler;
}

// properties

bool Packman::has_property (std::string property_name) const {
    if (property_name == "score")
        return true;
    if (property_name == "actor.packman")
        return true;
    if (property_name == "eat ghost")
        return eat_ghosts > 0;
    return false;
}

int Packman::get_property (std::string property_name) const {
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
