#ifndef MOVE_H_SENTRY
#define MOVE_H_SENTRY

#include <curses.h>
#include "state.h"

void show_message(int x, int y);

void move_message(int *x, int *y, const struct window_state *ws, int dx, int dy);

void handle_resize(int *x, int *y, struct window_state *ws);

#endif
