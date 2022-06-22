#ifndef PONG_PUCK_H_
#define PONG_PUCK_H_

#include <cairo.h>

class Puck {
    float px = 0.5,
        py = 0.5,
	    dx = 0.866,
	    dy = 0.5,
        speed = 0.3,
	    d2x = 0.01,
        rad = 0.02;
private:
    void set_random_start_orientation();
public:
    Puck() { set_random_start_orientation(); }
    void draw(int width, int height, cairo_t *cr) const;
    void tick(int time_diff);
    int check_wall_collision();
    void reverse_x() { dx *= -1; }

    float x() const { return px; }
    float y() const { return py; }
    float x_direction() const { return dx; }
    float radius() const { return rad; }

    void reset() {
        px = 0.5;
        py = 0.5;
        speed = 0.3;
        set_random_start_orientation();
    }
};

#endif
