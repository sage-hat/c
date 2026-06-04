/*
* Module:     game.c
* Author:     sage
* Created:    01.06.2026
* Modified:   03.06.2026
* Version:    0.1
* Description: Game control module
* 
* Comments: 
*/

#include "game.h"

static const char empty_ch = ' ';
static const char player_ch = '@';
static const char coin_ch = 'O';

static int rand_y(const struct game_state *gs)
/*Returns a random number for a range of Y*/
{
    return rand()%gs->height;
}

static int rand_x(const struct game_state *gs)
/*Returns a random number for a range of X*/
{
    return rand()%gs->width;
}

static void set_coins(char **gf, struct game_state *gs)
/*Spawns coins in random locations*/
{
    int i, y, x;
    for(i = 0; i < max_coins; i++) {
        y = rand_y(gs);
        x = rand_x(gs);
        gs->y_coins[i] = y;
        gs->x_coins[i] = x;
        gf[y][x]  = cell_coin;
    }
}

static void check_coin(char ***gf, struct game_state *gs)
/*Checks whether the player has collected a coin*/
{
    int i;
    for(i = 0; i < max_coins; i++) {
        if((gs->py == gs->y_coins[i]) && (gs->px == gs->x_coins[i])) {
            (*gf)[gs->y_coins[i]][gs->x_coins[i]] = cell_empty;
            gs->y_coins[i] = -1;
            gs->x_coins[i] = -1;
            gs->score++;
        }
    }
}

static void check_level(struct game_state *gs)
/*Check if the goal has been achieved. If successful, level up*/
{
    if(gs->score == gs->score_goal) {
        gs->level++;
        gs->score_goal += max_coins;
        gs->is_lvlup = 1;
    }
}

static int gf_allocate(char **gf, const struct game_state *gs)
/*Allocates memory for the game field lines*/
{
    int status, i;
    status = 0;
    for(i = 0; i < gs->height; i++) {
        char *gf_line;
        gf_line = malloc((gs->width + 1)*sizeof(char));
        if(gf_line == NULL) {
            return ERR_MEMORY;
        }
        gf[i] = gf_line;
    }
    gf[gs->height]= NULL;
    return status;
}

static void gf_free(char **gf)
/*Frees up the memory of the array with game fields*/
{
    int i;
    for(i = 0; gf[i] != NULL; i++) {
        free(gf[i]);
    }
    free(gf);
}

static void set_gf(char **gf, const struct game_state *gs)
/*Initializes the playing field, fills it with empty codes*/
{
    int i, j;
    for(i = 0; i < gs->height; i++) {
        for(j = 0; j < gs->width; j++) {
            gf[i][j] = cell_empty;
        }
        gf[i][gs->width] = '\0';
    }
}

static int init_game_field(char **gf, const struct game_state *gs)
/*Initializes the game field*/
{
    int status = 0;
    status = gf_allocate(gf, gs);
    if(status) {
        return status;
    }
    set_gf(gf, gs);
    return status;
}

static void init_playeryx(struct game_state *gs, char **gf)
/*Initializes the  player's starting position*/
{
    gf[gs->py][gs->px] = cell_player;
}

static void init_gs(struct game_state *gs, window_state_t *ws)
/*Initializes the game state*/
{
    int top_max_y, bottom_max_y, right_max_x, left_max_x, ui_top, ui_bottom;
    top_max_y = lgl_get_play_field_top(ws);
    bottom_max_y = lgl_get_play_field_bottom(ws);
    right_max_x = lgl_get_play_field_right(ws);
    left_max_x = lgl_get_play_field_left(ws);
    ui_top = lgl_get_ui_top(ws);
    ui_bottom = lgl_get_ui_bottom(ws);

    gs->height = bottom_max_y - top_max_y + 1;
    gs->width = right_max_x - left_max_x + 1;

    gs->offset_y = top_max_y;
    gs->offset_x = left_max_x;

    gs->uit_y = ui_top;
    gs->uib_y = ui_bottom;

    gs->py = 0;
    gs->px = 0;
    gs->score = 0;
    gs->score_goal = max_coins;
    gs->level = 0;
    gs->is_lvlup = 0;
    gs->resize_pendind = 0;
}

static void reload_gs(struct game_state *gs, window_state_t *ws)
/*Resets the game state*/
{

    int top_max_y, bottom_max_y, right_max_x, left_max_x, ui_top, ui_bottom;
    top_max_y = lgl_get_play_field_top(ws);
    bottom_max_y = lgl_get_play_field_bottom(ws);
    right_max_x = lgl_get_play_field_right(ws);
    left_max_x = lgl_get_play_field_left(ws);
    ui_top = lgl_get_ui_top(ws);
    ui_bottom = lgl_get_ui_bottom(ws);

    gs->height = bottom_max_y - top_max_y + 1;
    gs->width = right_max_x - left_max_x + 1;

    gs->offset_y = top_max_y;
    gs->offset_x = left_max_x;

    gs->uit_y = ui_top;
    gs->uib_y = ui_bottom;

    gs->py = 0;
    gs->px = 0;
}

static int adjust_x(const struct game_state *gs, int nx)
/*Checks for going beyond the game field by X*/
{
    if(nx >= gs->width) {
        return nx - 1;
    } else if(nx < 0 ) {
        return 0;
    } else {
        return nx;
    }

}

static int adjust_y(const struct game_state *gs, int ny)
/*Checks for going beyond the game field by Y*/
{
    if(ny >= gs->height) {
        return ny - 1;
    } else if(ny < 0) {
        return 0;
    } else {
        return ny;
    }
}

static void move_horizontal(char **gf, struct game_state *gs, int nx)
/*Horizontal movement of an object*/
{
    gf[gs->py][gs->px] = cell_empty;
    gs->px = adjust_x(gs, nx);
    gf[gs->py][gs->px] = cell_player;
}

static void move_vertical(char **gf, struct game_state *gs, int ny)
/*Vertical movement of an object*/
{
    gf[gs->py][gs->px] = cell_empty;
    gs->py = adjust_y(gs, ny);
    gf[gs->py][gs->px] = cell_player;
}

static void render_gf(char **gf, const struct game_state *gs)
/*Renders the game board and displays symbols according to the code*/
{
    int i, j;
    for(i = 0; i < gs->height; i++) {
        for(j = 0; j < gs->width; j++) {
            enum cell_code current_cell;
            current_cell = gf[i][j];
            switch(current_cell) {
                case cell_empty:
                    move(gs->offset_y + i, gs->offset_x + j);
                    addch(empty_ch);
                    break;
                case cell_player:
                    move(gs->offset_y + i, gs->offset_x + j);
                    addch(player_ch);
                    break;
                case cell_coin:
                    move(gs->offset_y + i, gs->offset_x + j);
                    addch(coin_ch);
                    break;
            }
        }
    }
}

static void render_horizontal(char **gf, const struct game_state *gs, int cy)
/*Displays the game field and symbols according to the code, along the Y-axis*/
{
    int i;
    for(i = 0; i < gs->width; i++) {
        enum cell_code current_cell;
        current_cell = gf[cy][i];
        switch(current_cell) {
            case cell_empty:
                move(gs->offset_y + cy, gs->offset_x + i);
                addch(empty_ch);
                break;
            case cell_player:
                move(gs->offset_y + cy, gs->offset_x + i);
                addch(player_ch);
                break;
            case cell_coin:
                move(gs->offset_y + cy, gs->offset_x + i);
                addch(coin_ch);
                break;
        }
    }
}

static void render_vertical(char **gf, const struct game_state *gs, int cx)
/*Displays the game field and symbols according to the code, along the X-axis*/
{
    int i;
    for(i = 0; i < gs->height; i++) {
        enum cell_code current_cell;
        current_cell = gf[i][cx];

        switch(current_cell) {
                case cell_empty:
                    move(gs->offset_y + i, gs->offset_x + cx);
                    addch(empty_ch);
                    break;
                case cell_player:
                    move(gs->offset_y + i, gs->offset_x + cx);
                    addch(player_ch);
                    break;
                case cell_coin:
                    move(gs->offset_y + i, gs->offset_x + cx);
                    addch(coin_ch);
                    break;
        }
    }
}

static void resize_gf(char ***gf, struct game_state *gs, window_state_t *ws)
/*Resets the state of the playing field*/
{
    int status;

    gf_free(*gf);

    reload_gs(gs, ws);
    *gf = malloc((gs->height + 1)*sizeof(char*));
    if(*gf == NULL) {
        return;
    }
    status = init_game_field(*gf, gs);
    if(status) {
        gf_free(*gf);
        return;
    }

    init_playeryx(gs, *gf);
    set_coins(*gf, gs);
    render_gf(*gf, gs);
}

static void handle_key(char ***gf, struct game_state *gs, window_state_t *ws)
/*Processing keystrokes*/
{
    int key;
    key = getch();
    switch(key) {
        case KEY_UP:
            move_vertical(*gf, gs, gs->py - 1);
            render_vertical(*gf, gs, gs->px);
            break;
        case KEY_DOWN:
            move_vertical(*gf, gs, gs->py + 1);
            render_vertical(*gf, gs, gs->px);
            break;
    case KEY_LEFT:
            move_horizontal(*gf, gs, gs->px - 1);
            render_horizontal(*gf, gs, gs->py);
            break;
    case KEY_RIGHT:
            move_horizontal(*gf, gs, gs->px + 1);
            render_horizontal(*gf, gs, gs->py);
            break;
    case KEY_RESIZE:
             gs->resize_pendind = 1;
            break;
    case lgl_key_command:
            lgl_command_process(ws);
            break;
    }
}

void game_process(window_state_t *ws)
/*The main process of the game*/
{
    int status = 0;
    struct game_state gs;
    char **gf;
    init_gs(&gs, ws);

    gf = malloc((gs.height + 1)*sizeof(char*));
    if(gf == NULL) {
        return;
    }
    status = init_game_field(gf, &gs);
    if(status) {
        gf_free(gf);
        return;
    }

    init_playeryx(&gs, gf);
    set_coins(gf, &gs);
    render_gf(gf, &gs);

    for(;;) {
        check_coin(&gf, &gs);
        check_level(&gs);
        mvprintw(gs.uit_y, 0, "Score: %d", gs.score);
        mvprintw(gs.uib_y, 0, "Level: %d", gs.level);
        handle_key(&gf, &gs, ws);

        if(gs.resize_pendind && gs.is_lvlup) {
            lgl_execute_resize(ws);
            gs.resize_pendind = 0;
            resize_gf(&gf, &gs, ws);
            gs.is_lvlup = 0;
        }
        
        if(gs.is_lvlup) {
            resize_gf(&gf, &gs, ws);
            gs.is_lvlup = 0;
        }
        
    }
    gf_free(gf);
}

