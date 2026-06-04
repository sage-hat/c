#ifndef GAME_H_SENTRY
#define GAME_H_SENTRY

#include <stdlib.h>
#include <curses.h>
#include "lgl.h"


enum {max_coins = 15};

struct game_state {
    int height;
    int width;
    int offset_y;
    int offset_x;
    int py;
    int px;
    int score;
    int level;
    int score_goal;
    int is_lvlup;
    int resize_pendind;
    int y_coins[max_coins];
    int x_coins[max_coins];
    int uit_y;
    int uib_y;
};

enum cell_code {
    cell_empty = 1,
    cell_player,
    cell_coin
};

void game_process(window_state_t *ws);

#endif

