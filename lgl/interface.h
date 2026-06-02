#ifndef INTERFACE_H_SENTRY
#define INTERFACE_H_SENTRY

#include <curses.h>
#include "state.h"

enum render_mode {
    h_print = 1,
    h_clear = -1,
    v_print = 2,
    v_clear = -2,
};

void init_window(struct window_state *ws);
void execute_resize(struct window_state *ws);
void clear_line(int y, int x);
#endif

