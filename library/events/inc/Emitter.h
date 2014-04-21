#ifndef GUARD_EVENT_EMITTER
#define GUARD_EVENT_EMITTER

#include "Listener.h"

namespace events {
    template < typename Event_type >
    class Emitter {
        public:
            virtual ~Emitter<Event_type> () = default;

            virtual void set_output (Listener<Event_type>* listener) = 0;
    };
}

#endif // GUARD_EVENT_EMITTER
