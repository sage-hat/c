#ifndef MOVE_H_SENTRY
#define MOVE_H_SENTRY

#include <curses.h>

void show_message(int x, int y);

void move_message(int *x, int *y, int mx, int my, int dx, int dy);

void handle_resize(int *x, int * y, int *mx, int *my);
#endif
