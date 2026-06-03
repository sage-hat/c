#include "lgl_priv.h"

window_state_t* lgl_init(void)
{
    window_state_t *ws = malloc(sizeof(window_state_t));
    if (ws == NULL) {
        return NULL;
    }
                                
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    init_window(ws);
    return ws;
}

void lgl_cleanup(window_state_t *ws)
{
    if (ws != NULL) {
        free(ws);
    }
}
