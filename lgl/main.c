#include <curses.h>
#include "game.h"

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

#ifndef DEB

static void main_process()
{
    struct window_state ws;
    init_window(&ws);
    game_process(&ws);
    endwin();
}

int main()
{
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);

    main_process();

    return 0;
}
#else
int main(int, char **argv)
{
    int status;
    status = DEB_command_process(argv);
    return status;
}
#endif

