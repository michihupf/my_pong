#ifndef PONG_BUTTON_H_
#define PONG_BUTTON_H_

#include <cairo.h>
#include <string>
class GameButton {
        cairo_text_extents_t extents;
        float font_size;
        float x, y;
        std::string text;
    public:

        float subx = -1;
        float suby = -1;

        GameButton(std::string text) {
            this->text = text;
        }

        void set_text(std::string text) {
            this->text = text;
        }

        void set_font_size(float font_size) {
            this->font_size = font_size;
        }

        void set_location(float x, float y) {
            this->x = x;
            this->y = y;
        }

        void draw(cairo_t *cr);
        bool is_clicked(float *mouse_pointer) const;
        void compute_dimensions(cairo_t *cr);
};

#endif
