#include "World.h"

using namespace gamelogic;

World::World(Level level) : level(level){
}


void World::spawn_actor (std::shared_ptr<Actor> actor) {
    actors.push_back(actor);
    next_turn_broadcaster.subscribe(actor.get());
    powerup_broadcaster.subscribe(actor.get());
    actor_collision_broadcaster.subscribe(actor.get());
    actor_movement_broadcaster.subscribe(actor.get());
}

void World::spawn_powerup (std::shared_ptr<Powerup> powerup) {
    powerups.push_back(powerup);
    powerup_broadcaster.subscribe(powerup.get());
}

void World::kill_actor (const Actor* actor) {
    actors.erase(std::remove_if(actors.begin(), actors.end(), 
                [&](std::shared_ptr<Actor> a){return a.get() == actor;}), actors.end());
}


void World::handle_event (Actor_movement_event& event) {
    Actor* other_actor = get_actor_at(event.get_new_position());
    if (other_actor != nullptr) {
        Actor_collision_event collision(event.get_actor(), other_actor);
        actor_collision_broadcaster.handle_event(collision);

        other_actor = get_actor_at(event.get_new_position());
    }

    Powerup* powerup = get_powerup_at(event.get_new_position());
    if (powerup != nullptr) {
        Powerup_event powerup_event(event.get_actor(), powerup);
        powerup_broadcaster.handle_event(powerup_event);

        powerup = get_powerup_at(event.get_new_position());
    }

    Tile* tile = level.get_tile_at(event.get_new_position());

    if (other_actor == nullptr && powerup == nullptr && tile == nullptr) {
        actor_movement_broadcaster.handle_event(event);
    }
}

void World::next_turn () {
    Next_turn_event next_turn(this);
    next_turn_broadcaster.handle_event(next_turn);
}


events::Service<Next_turn_event>& World::get_turns_service () {
    return next_turn_broadcaster;
}

events::Service<Powerup_event>& World::get_powerup_service () {
    return powerup_broadcaster;
}

events::Service<Actor_collision_event>& World::get_actor_collision_service () {
    return actor_collision_broadcaster;
}

events::Service<Actor_movement_event>& World::get_actor_movement_service () {
    return actor_movement_broadcaster;
}

const Level& World::get_level () const {
    return level;
}


// private functions
Actor* World::get_actor_at (geom2d::Vector<int> position) {
    auto at = std::find_if (actors.begin(), actors.end(),
            [&](std::shared_ptr<Actor> a){return a->get_position() == position;});
    if (at == actors.end())
        return nullptr;
    return at->get();
}

Powerup* World::get_powerup_at (geom2d::Vector<int> position) {
    auto at = std::find_if (powerups.begin(), powerups.end(),
            [&](std::shared_ptr<Powerup> p){return p->get_position() == position;});
    if (at == powerups.end())
        return nullptr;
    return at->get();
}


// Commented out functions
/*
Entity& World::get_entity_at (geom2d::Vector<int> position) {
    auto at = std::find_if (entities.begin(), entities.end(),
            [&](std::shared_ptr<Entity> e){return e->get_position() == position;});
    return **at;
}
*/
/*
void World::kill_entity (Entity& entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), 
                [&](std::shared_ptr<Entity> e){return *e == entity;}), entities.end());
}
*/
/*
void World::spawn_entity (std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}
*/
