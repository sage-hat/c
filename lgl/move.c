#include "move.h"


static const char message[] = "@";
enum {key_escape = 27};

void show_message(int x, int y)
{
    move(y,x);
    addstr(message);
    refresh();
}

static void hide_message(int x, int y)
{
    int i;
    move(y, x);
    for(i = 0; i < (int)sizeof(message) - 1; i++) {
        addch(' ');
    }
    refresh();
}

static void check(int *coord, int max)
{
    if(*coord < 0)
        *coord = 0;
    else
    if(*coord > max)
        *coord = max;
}

void move_message(int *x, int *y, int mx, int my, int dx, int dy)
{
    hide_message(*x, *y);
    *x += dx;
    check(x, mx);
    *y += dy;
    check(y, my);
    show_message(*x, *y);
}

void handle_resize(int *x, int * y, struct window_state *ws)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    ws->max_x = col - sizeof(message) + 1;
    ws->max_y = row - 1;
    hide_message(*x, *y);
    check(x, ws->max_x);
    check(y, ws->max_y);
    show_message(*x, *y);
}
