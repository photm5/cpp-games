#ifndef GUARD_GAMELOGIC_ENTITY
#define GUARD_GAMELOGIC_ENTITY

#include <string>

#include "library/events/inc/Listener.h"

#include "library/geom2d/inc/Vector.h"

#include "Powerup_event.h"

namespace gamelogic {

    class Entity : public events::Listener<Powerup_event> {
        public:
            Entity (geom2d::Vector<int> pos);
            virtual ~Entity () = default;

            virtual bool operator== (const Entity& other);

            geom2d::Vector<int> get_position () const;
            void set_position (geom2d::Vector<int> position);

            virtual bool has_property (std::string property_name) const;
            virtual int get_property (std::string property_name) const;

        protected:
            geom2d::Vector<int> position;
    };

}

#endif // GUARD_GAMELOGIC_ENTITY
