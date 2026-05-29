#include <curses.h>
#include <stdlib.h>
#include "string.h"
#include "move.h"
#include "parse.h"

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

#ifndef DEB
static const char message[] = "@";



#endif

#ifndef DEB

static void init_cmd_pos(struct window_state *ws)
/*Sets the values of y for command line input and output.*/
{
    ws->cmd_input = ws->max_y;
    ws->cmd_output = ws->cmd_input - 1;

}

static void set_win_coords(struct window_state *ws)
{
    init_cmd_pos(ws);
}

int main()
{
    int status;
    struct window_state ws;

    int row, col, x, y, key;
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    getmaxyx(stdscr, row, col);
    x = (col -(sizeof(message)-1)) / 2;
    y = row/2;
    ws.max_x = col - sizeof(message) + 1;
    ws.max_y = row - 1;
    set_win_coords(&ws);
    show_message(x, y);
    refresh();
    while((key = getch()) != key_escape) {
        switch(key) {
        case KEY_UP:
            move_message(&x, &y, ws.max_x, ws.max_y, 0, -1);
            break;
        case KEY_DOWN:
            move_message(&x, &y, ws.max_x, ws.max_y, 0, 1);
            break;
            case KEY_LEFT:
            move_message(&x, &y, ws.max_x, ws.max_y, -1, 0);
            break;
        case KEY_RIGHT:
            move_message(&x, &y, ws.max_x, ws.max_y, 1, 0);
            break;
        case KEY_RESIZE:
            handle_resize(&x, &y, &ws);
            set_win_coords(&ws);
            break;
        case key_command:
            status = command_process(&ws);
            break;
        }
    }
    endwin();
    return status;
}
#else
int main(int, char **argv)
{
    int status;
    status = DEB_command_process(argv);
    return status;
}
#endif

