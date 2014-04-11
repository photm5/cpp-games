#ifndef GUARD_EVENT_LISTENER
#define GUARD_EVENT_LISTENER

namespace event {
    template < typename Event_type >
    class Listener {
        public:
            virtual ~Listener<Event_type> () = default;

            virtual void handle_event (Event_type& event) = 0;
    };
}

#endif // GUARD_EVENT_LISTENER
