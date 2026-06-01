#include <curses.h>
#include <stdlib.h>
#include "string.h"
#include "move.h"
#include "parse.h"
#include "interface.h"

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

#ifndef DEB
int main()
{
    int status;
    struct window_state ws;

    int x, y, key;
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);

    init_game(&ws, &x, &y);
   while((key = getch()) != key_escape) {
        switch(key) {
        case KEY_UP:
            move_message(&x, &y, &ws, 0, -1);
            break;
        case KEY_DOWN:
            move_message(&x, &y, &ws, 0, 1);
            break;
            case KEY_LEFT:
            move_message(&x, &y, &ws, -1, 0);
            break;
        case KEY_RIGHT:
            move_message(&x, &y, &ws, 1, 0);
            break;
        case KEY_RESIZE:
            execute_resize(&ws, &x, &y);
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

