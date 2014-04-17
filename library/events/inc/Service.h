#ifndef GUARD_EVENT_SERVICE
#define GUARD_EVENT_SERVICE

#include "Listener.h"

namespace events {
    template < typename Event_type >
    class Service {
        public:
            virtual ~Service<Event_type> () = default;

            virtual void subscribe (Listener<Event_type>& listener) = 0;
            virtual void de_subscribe (Listener<Event_type>& listener) = 0;
    };
}

#endif // GUARD_EVENT_SERVICE
