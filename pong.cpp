#include "gui.h"

#include "pong.h"
#include "player.h"
#include "puck.h"
#include "button.h"

using std::cout, std::endl, std::string;
using std::max;


enum game_state { INIT, PLAY, PAUSE, GAMEOVER };
game_state state = INIT;

GameButton play_button("Play [SPACE]"),
           quit_button("[Q]uit");

Puck puck;
Player p1(.02), p2(.98);

bool pause_key_pressed = false;

void draw(int width, int height, cairo_t *cr) {
	cairo_set_line_width(cr, max(0.004*width,1.0));
	cairo_set_source_rgb(cr, 1, 1, 1);

	// Hier ist etwas zu tun
    if (state == PLAY) {
        puck.draw(width, height, cr);
        p1.draw(width, height, cr);
        p2.draw(width, height, cr);
    } else if (state == INIT) {
        cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

        play_button.set_font_size(0.04*width);
        play_button.set_location(0.5*width, 0.5*height);
        play_button.draw(cr);

        quit_button.set_font_size(0.02*width);
        quit_button.set_location(0.5*width, 0.85*height);
        quit_button.draw(cr);
    } else if (state == PAUSE) {
        cairo_text_extents_t extents;

        char *pause_text = (char*) "Game is paused";
        char *esc_to_resume_text = (char*) "[ESC] to resume";

        cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 0.04*width);
        cairo_text_extents(cr, esc_to_resume_text, &extents);

        cairo_move_to(cr, 0.5*width - 0.5*extents.width, 0.5*height - 0.5*extents.height);
        cairo_show_text(cr, esc_to_resume_text);

        cairo_set_font_size(cr, 0.06*width);
        cairo_text_extents(cr, pause_text, &extents);

        cairo_move_to(cr, 0.5*width - 0.5*extents.width, 0.4*height - 0.5*extents.height);
        cairo_show_text(cr, pause_text);

        quit_button.set_font_size(0.02*width);
        quit_button.set_location(0.5*width, 0.85*height);
        quit_button.draw(cr);
    } else if (state == GAMEOVER) {
        // maybe draw stuff?
    }
}

void tick(int time_diff) {

    // Hier ist etwas zu tun
    if (state == PLAY) {
        if (key_pressed(ESC_KEY)) {
            if (!pause_key_pressed) {
                state = PAUSE;
                pause_key_pressed = true;
            }
        } else 
            pause_key_pressed = false;
        p1.stop();
        p2.stop();
        if (key_pressed('w') || key_pressed('W')) {
            p1.move_up();
        }
        if (key_pressed('o') || key_pressed('O')) {
            p2.move_up();
        }
        if (key_pressed('s') || key_pressed('S')) {
            p1.move_down();
        }
        if (key_pressed('l') || key_pressed('L')) {
            p2.move_down();
        }

        // check puck collisions with wall
        int winner = puck.check_wall_collision();
        if (winner == 1) {
            p1.win();
            state = GAMEOVER;
            return;
        }
        if (winner == 2) {
            p2.win();
            state = GAMEOVER;
            return;
        }
        
        // check puck collisions with player
        if ((p1.touches_puck(puck) && puck.x_direction() < 0) || (p2.touches_puck(puck) && puck.x_direction() > 0)) {
            puck.reverse_x();
        }

        // check if puck out of bounds
        if (p1.out_of_bounds(0.01)) {
            p1.stop();
        }
        if (p2.out_of_bounds(0.01)) {
            p2.stop();
        }

        // handle puck physics
        puck.tick(time_diff); 

        // handle player physics
        p1.tick(time_diff);
        p2.tick(time_diff);

    } else if (state == INIT) {
        if (key_pressed(' ')) {
            state = PLAY;
        }
        // check mouse pointer
        float *mouse_pointer = get_mouse_click();
        if (play_button.is_clicked(mouse_pointer))
            state = PLAY;
        else
            quit_if_needed(mouse_pointer);
    } else if (state == PAUSE) {
        if (key_pressed(ESC_KEY)) {
            if (!pause_key_pressed) {
                state = PLAY;
                pause_key_pressed = true;
            }
        } else
            pause_key_pressed = false;
        float *mouse_pointer = get_mouse_click();
        quit_if_needed(mouse_pointer);
    } else if (state == GAMEOVER) {
        p1.reset(.02);
        p2.reset(.98);
        puck.reset();
        state = PLAY;
    }
}

void quit_if_needed(float *mouse_pointer) {
    if (quit_button.is_clicked(mouse_pointer))
        quit_gui();
    else if (key_pressed('q') || key_pressed('Q'))
        quit_gui();
}

int main(int argc, char *argv[])
{
	tick_callback = tick;
	draw_callback = draw;
	start_gui(700, 400);

	return 0;
}
