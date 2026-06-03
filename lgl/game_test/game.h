#ifndef GAME_H_SENTRY
#define GAME_H_SENTRY

#include <stdlib.h>
#include <curses.h>
#include "lgl.h"

enum cell_code {
    cell_empty = 1,
    cell_player,
    cell_coin
};

void game_process(struct window_state *ws);

#endif

