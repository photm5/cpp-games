#ifndef GUARD_GUI_DRAW_EVENT
#define GUARD_GUI_DRAW_EVENT

#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI {

    class Draw_event {
        public:
            Draw_event (sf::RenderTarget& render_target);

            sf::RenderTarget& get_target () const;

        protected:
            sf::RenderTarget& render_target;

    };

}

#endif // GUARD_GUI_DRAW_EVENT
