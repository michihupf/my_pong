#include "gui.h"

#include <random>
#include <iostream>

/* Der Inhalt dieser Datei muss nicht nachvollzogen werden können, hier stehen die
 * Details um die einfache Verwendung im Spiel möglich zu machen.
 * Sie dürfen natürlich gern genauer reinlesen -- nur müssen Sie es nicht :)
 */

static gint64 timer_start = 0;
static gint64 last_time = 0;
void (*tick_callback)(int time_diff) = nullptr;
void (*draw_callback)(int width, int height, cairo_t *cr) = nullptr;

static gboolean tick(GtkWidget *widget, GdkFrameClock *clock, gpointer user_data) {
	if (timer_start == 0) {
		timer_start = gdk_frame_clock_get_frame_time(clock);
		last_time = 0;
		return TRUE;
	}
	gint64 time =  (gdk_frame_clock_get_frame_time(clock) - timer_start) / 1000;
	gint64 time_diff = time - last_time;

	tick_callback(time_diff);
	
	gtk_widget_queue_draw(widget);
	last_time = time;
	return TRUE;
}

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	GtkWidget *win = gtk_widget_get_toplevel(widget);
	int width, height;
	gtk_window_get_size(GTK_WINDOW(win), &width, &height);

	draw_callback(width, height, cr);
	return TRUE;
}

static int pressed[256];

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
	if (strlen(event->string) > 0) {
		pressed[event->string[0]] = 1;
		return TRUE;
	}
	return FALSE; // to fall through
}

static gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
	if (strlen(event->string) > 0) {
		pressed[event->string[0]] = 0;
		return TRUE;
    }
	return FALSE;
}

bool key_pressed(char c) {
	return pressed[c] != 0;
}

// array for saving x and y coordinates of a mouse click. Initialize with {-1,-1} as {0,0} 
// would mean a click in the top left corner.
static float mouse_pointer[2] = {-1, -1};

static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event) {
    mouse_pointer[0] = event->x;
    mouse_pointer[1] = event->y;
    return TRUE;
}

static gboolean on_button_release(GtkWidget *widget, GdkEventButton *event) {
    mouse_pointer[0] = -1.;
    mouse_pointer[1] = -1.;
    return TRUE;
}

float* get_mouse_click() {
    return mouse_pointer;
}

void start_gui(int w, int h) {

	char *args[] = { (char*)"ui-prog", nullptr };
	char **argv = args;
	int argc = 1;
	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkCssProvider *css_prov = gtk_css_provider_new();
	gtk_css_provider_load_from_data(css_prov, "* { background-image:none; background-color:black; }", -1, nullptr);
	GtkStyleContext *style_ctx = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider(style_ctx, GTK_STYLE_PROVIDER(css_prov), GTK_STYLE_PROVIDER_PRIORITY_USER);

	GtkWidget *darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), darea);

	gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

	g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(draw), NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(on_key_press), NULL);
	g_signal_connect(G_OBJECT(window), "key_release_event", G_CALLBACK(on_key_release), NULL);
    // mouse button pressing
    g_signal_connect(G_OBJECT(window), "button_press_event", G_CALLBACK(on_button_press), NULL);
    g_signal_connect(G_OBJECT(window), "button_release_event", G_CALLBACK(on_button_release), NULL);
	gtk_widget_add_tick_callback(window, tick, nullptr, nullptr);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), w, h); 
	gtk_window_set_title(GTK_WINDOW(window), "PG2 | P0NG");

    /*  code for fullscreening the window (comment this out if debugging / testing). This is quite annoying in the development process.
        depending on your window manager this could just fail. This is nothing to worry about. */
    gtk_window_fullscreen(GTK_WINDOW(window));
	gtk_widget_show_all(window);
	gtk_main();
}

void quit_gui() {
	gtk_main_quit(); 
}

void draw_circle(cairo_t *cr, int x, int y, int rad) {
	cairo_translate(cr, x, y);
	cairo_new_path(cr);
	cairo_arc(cr, 0, 0, rad, 0, 2 * M_PI);
	cairo_stroke(cr);
	cairo_translate(cr, -x, -y);
}

void draw_rectangle(cairo_t *cr, int x, int y, int width, int height) {
    cairo_translate(cr, x, y);
    cairo_new_path(cr);
    cairo_rectangle(cr, 0, 0, width, height);
	cairo_fill(cr);
    cairo_translate(cr, -x, -y);
}

float random_number() {
	static std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0f, 1.0f);
	return dist(mt);
}
