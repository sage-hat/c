#ifndef INTERFACE_H_SENTRY
#define INTERFACE_H_SENTRY

#include <curses.h>
#include "state.h"
/*temp*/
#include "move.h"


enum render_mode {
    h_print = 1,
    h_clear = -1,
    v_print = 2,
    v_clear = -2,
};

void init_game(struct window_state *ws, int *x, int *y);
void execute_resize(struct window_state *ws, int *x, int *y);
void set_border(const struct window_state *ws);
void clear_line(int y, int x);
#endif
