#include "Draw_event.h"

using namespace GUI;

Draw_event::Draw_event (sf::RenderTarget& render_target) : render_target(render_target) {
}

sf::RenderTarget& Draw_event::get_target () const {
    return render_target;
}
