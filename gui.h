#include <cairo.h>
#include <gtk/gtk.h>

/* Funktion die regelmäßig aufgerufen wird um den aktuellen Zustand des Spiel zu bestimmen.
 * Übergeben wird die Zeit die seit dem letzten aktualisieren vergangen ist (in Millisekunden)
 */
extern void (*tick_callback)(int time_diff);

/* Funktion die den aktuellen Spielzustand anzeigt.
 * Übergeben wird die Größe des Fensters und ein "Cairo Objekt" das an die
 * Funktionen zum Zeichnen übergeben werden msus
 */
extern void (*draw_callback)(int width, int height, cairo_t *cr);

/* Mit dieser Funktion wird die Kontrolle des Programms an die GUI übergeben.
 */
void start_gui(int w, int h);

/* Mit dieser Funktion kann die GUI "ordnungsgemäß" beendet werden, der
 * `start_gui' Aufruf kehrt dann zurück.
 */
void quit_gui();

/* Mit dieser Funktion kann abgefragt werden, ob eine bestimmte Taste aktuelle gedrückt ist.
 * Geht in der Form nur für Zeichen im erweiterten ASCII Raum, das ist nicht besonders gut,
 * genügt aber für den Moment.
 */
bool key_pressed(char c);

/** Mit dieser Funktion lassen sich die Koordinaten eines Mausklicks ausgeben. Falls kein Klick stattgefunden hat ist die Rückgabe [-1,-1].
 *
 * @returns Coordinates of a mouse click [x,y]. If no click happend returns [-1,-1].
 * author: Michael Hupf
 */
float* get_mouse_click();

/* Kleine Hilfe: Auch ESC hat einen gültigen ASCII Code. Die Konstante kann an
 * `key_pressed' übergeben werden.
 */
const char ESC_KEY = 033;

/* Erzeugt eine zufällige Zahl zwischen 0 und 1.
 * Details: Die Zahlen sind sehr gut und uniform in der Domäne verteilt.
 */
float random_number();

/* Zeichnet einen Kreis mit Radius `rad' an der Position `x', `y'
 */
void draw_circle(cairo_t *cr, int x, int y, int rad);
void draw_rectangle(cairo_t *cr, int x, int y, int width, int height);
