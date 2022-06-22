#include "puck.h"
#include "gui.h"
#include "player.h"
#include <random>
#include <cmath>
#include <iostream>

int Puck::check_wall_collision() {
    if (px + rad > 1) {
        return 1;
    }
    if (px - rad < 0) {
        return 2;
    }
    if (py + rad > 1)
        dy = -1;
    if (py - rad < 0)
        dy = 1;
    return 0;
}

void Puck::tick(int time_diff) {
    float c = speed * time_diff / 1000.;
    px += dx * c;
    py += dy * c;
    speed += d2x * time_diff / 1000.;
}

void Puck::draw(int width, int height, cairo_t *cr) const {
    draw_circle(cr, px*width, py*height, rad*width);
}

void Puck::set_random_start_orientation() {
    std::random_device rd;
    std::mt19937 rng(rd());
    // uniform distribution from 0 to pi/8
    double pi8 = .39269908169;
    double pi12 = .26179938779;
    std::uniform_real_distribution<> distr(pi8);
    double ran = distr(rng);
    // shifting angle by pi/12 to create gap around 0deg
    dx = cos(ran+pi12);
    dy = sin(ran+pi12);
    // flip x coordinate for vertical symmetry
    if (rand() % 2 == 0)
        dx = -dx;
    // flip y coordinate for horizontal symmetry
    if (rand() % 2 == 0)
        dy = -dy;
            
}
