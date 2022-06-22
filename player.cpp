#include "player.h"
#include "gui.h"
#include <string>
#include <sstream>

void Player::draw(int width, int height, cairo_t *cr) const {
    draw_rectangle(cr, (pos_x - this->width / 2) * width, 
            (pos_y - this->height / 2) * height, this->width * width, this->height * height);
    // draw name and points for player
    // draw points in the respective upper corner
    {
        float points_x = .2;
        if (this->pos_x > .5)
            points_x = .8;

        std::ostringstream oss;
        oss << this->points;
        std::string pnts = oss.str();
        cairo_text_extents_t extents;

        cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 0.06*width);
        cairo_text_extents(cr, pnts.data(), &extents);

        cairo_move_to(cr, points_x*width - 0.5*extents.width, .15*height - 0.5*extents.height);
        cairo_show_text(cr, pnts.data());
    }
}

void Player::tick(int time_diff) {
    pos_y += dy * time_diff / 1000.;
}

bool Player::touches_puck(const Puck &puck) const {
    if (pos_x > .5)
        return 
            puck.y() - puck.radius() < pos_y + height / 2 &&
            puck.y() + puck.radius()> pos_y - height / 2 &&
            puck.x() + puck.radius() > pos_x - width / 2;
    else
        return 
            puck.y() - puck.radius() < pos_y + height / 2 &&
            puck.y() + puck.radius() > pos_y - height / 2 &&
            puck.x() - puck.radius() < pos_x + width / 2;
}

bool Player::out_of_bounds(float border_width) const {
    return 
        (pos_y > 1 - border_width - height/2 && dy > 0) ||
        (pos_y < border_width + height/2 && dy < 0);
}
