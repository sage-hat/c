#include <curses.h>
#include <time.h>
#include "game.h"
#include "lgl.h"

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

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

    srand(time(NULL));

    main_process();

    return 0;
}

