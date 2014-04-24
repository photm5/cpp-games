#ifndef GUARD_EVENTS_FORWARDER
#define GUARD_EVENTS_FORWARDER

#include "Listener.h"
#include "Emitter.h"

namespace events {

    template<typename Event_type>
    class Forwarder : public Listener<Event_type>, public Emitter<Event_type> {
        public:
            Forwarder (Listener<Event_type>* listener);
            Forwarder ();
            virtual ~Forwarder () = default;

            void handle_event (Event_type& event);
            void set_output (Listener<Event_type>* listener);

        private:
            Listener<Event_type>* listener;
    };

    template<typename Event_type>
    Forwarder<Event_type>::Forwarder () {
        listener = nullptr;
    }

    template<typename Event_type>
    Forwarder<Event_type>::Forwarder (Listener<Event_type>* listener) {
        this->listener = listener;
    }

    template<typename Event_type>
    void Forwarder<Event_type>::handle_event (Event_type& event) {
        if (listener != nullptr) {
            listener->handle_event(event);
        }
    }

    template<typename Event_type>
    void Forwarder<Event_type>::set_output (Listener<Event_type>* listener) {
        this->listener = listener;
    }

}

#endif // GUARD_EVENTS_FORWARDER
