#include "button.h"

void GameButton::draw(cairo_t *cr) {
    cairo_set_font_size(cr, font_size);
    compute_dimensions(cr);

    cairo_rectangle(cr, x - extents.x_bearing - 0.5*extents.width - subx, 
            y + extents.y_bearing - 0.5*extents.height - suby, 
            extents.width + 2*subx, extents.height + 2*suby);
    cairo_move_to(cr, x - 0.5*extents.width, y - 0.5*extents.height);
    cairo_show_text(cr, text.c_str());
    cairo_stroke(cr);
}

bool GameButton::is_clicked(float *mouse_pointer) const {
    if (mouse_pointer[0] < 0) 
        return false;
    return 
        mouse_pointer[0] > x - extents.x_bearing - 0.5*extents.width - subx &&
        mouse_pointer[0] < x - extents.x_bearing + 0.5*extents.width + subx &&
        mouse_pointer[1] > y + extents.y_bearing - 0.5*extents.height - suby &&
        mouse_pointer[1] < y + extents.y_bearing + 0.5*extents.height + subx;
}

void GameButton::compute_dimensions(cairo_t *cr) {
    cairo_text_extents(cr, text.c_str(), &extents);
    subx = 0.4*extents.width;
    suby = 0.4*extents.height;
}
