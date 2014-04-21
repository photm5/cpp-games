#ifndef GUARD_EVENTS_LAMBDA_LISTNER
#define GUARD_EVENTS_LAMBDA_LISTNER

#include "Listener.h"

namespace events {
    template <typename Event_type, typename F>
    class Lambda_listener : public Listener<Event_type> {
        public:
            Lambda_listener (F func) : func(func) {
            };

            void handle_event (Event_type& event) {
                func(event);
            };

        private:
            F func;
    };

    template <typename Event_type, typename F>
    Lambda_listener<Event_type, F> mk_lambda (F func) {
        return Lambda_listener<Event_type, F>(func);
    }
}

#endif // GUARD_EVENTS_LAMBDA_LISTNER
