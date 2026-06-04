#include <curses.h>
#include <time.h>
#include "game.h"
#include "lgl.h"

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

static void main_process()
{
    window_state_t *ws;
    ws = lgl_init();
    game_process(ws);
    lgl_cleanup(ws);
}

int main()
{
    /*
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
*/
    srand(time(NULL));

    main_process();

    return 0;
}

