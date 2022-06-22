#ifndef PONG_PLAYER_H_
#define PONG_PLAYER_H_

#include <string>
#include <cairo.h>
#include "puck.h"

class Player {
    std::string name;
    const float width = .01;
    const float height = .2;
    const float speed = .5;
    float pos_x, pos_y = .5;
    float dy = 0;
    int points = 0;
public:

    Player() : pos_x(.5) {}
    Player(std::string name) : name(name), pos_x(.5) {}
    Player(float pos_x, float pos_y = .5) : pos_x(pos_x),
        pos_y(pos_y) {}
    Player(std::string name, float pos_x, float pos_y = .5) :
        name(name), pos_x(pos_x), pos_y(pos_y) {}
     
    void draw(int width, int height, cairo_t *cr) const;
    void tick(int time_diff);
    bool touches_puck(const Puck &puck) const;
    bool out_of_bounds(float border_width) const;
    void move_up() { dy = -speed; }
    void move_down() { dy = speed; }
    void stop() { dy = 0; }

    void win() { points++; }
    void reset(float x) {
        pos_x = x;
        pos_y = .5;
    }
};

#endif
