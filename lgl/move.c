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
    for(i = 0; i < sizeof(message) - 1; i++) {
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

void handle_resize(int *x, int * y, int *mx, int *my)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    *mx = col - sizeof(message) + 1;
    *my = row - 1;
    hide_message(*x, *y);
    check(x, *mx);
    check(y, *my);
    show_message(*x, *y);
}
