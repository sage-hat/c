#ifndef MOVE_H_SENTRY
#define MOVE_H_SENTRY

#include <curses.h>
struct window_state {
    int max_y;
    int max_x;
    int cmd_input;
    int cmd_output;
};

void show_message(int x, int y);

void move_message(int *x, int *y, int mx, int my, int dx, int dy);

void handle_resize(int *x, int * y, struct window_state *ws);
#endif
