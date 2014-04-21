#ifndef GUARD_GAMELOGIC_ACTOR_COLLISION_EVENT
#define GUARD_GAMELOGIC_ACTOR_COLLISION_EVENT

namespace gamelogic {
    class Actor;

    class Actor_collision_event {
        public:
            Actor_collision_event (Actor* executing, Actor* target);

            Actor* get_executing_actor () const;
            Actor* get_target_actor () const;

        private:
            Actor* executing;
            Actor* target;

    };

}

#endif // GUARD_GAMELOGIC_ACTOR_COLLISION_EVENT
