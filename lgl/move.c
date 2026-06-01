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

static void check_x(int *coord, const struct window_state *ws)
{
    if(*coord < ws->left_max_x)
        *coord = ws->left_max_x;
    else
    if(*coord > ws->right_max_x)
        *coord = ws->right_max_x;
}

static void check_y(int *coord, const struct window_state *ws)
{
    if(*coord < ws->top_max_y)
        *coord = ws->top_max_y;
    else
    if(*coord > ws->bottom_max_y)
        *coord = ws->bottom_max_y;
}

void move_message(int *x, int *y, const struct window_state *ws, int dx, int dy)
{
    hide_message(*x, *y);
    *x += dx;
    check_x(x, ws);
    *y += dy;
    check_y(y, ws);
    show_message(*x, *y);
}

void handle_resize(int *x, int *y, struct window_state *ws)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    ws->max_x = col - sizeof(message) + 1;
    ws->max_y = row - 1;
    hide_message(*x, *y);
    check_x(x, ws);
    check_y(y, ws);
    show_message(*x, *y);
}
