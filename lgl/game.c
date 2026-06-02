/*
* Module:     game.c
* Author:     sage
* Created:    01.06.2026
* Modified:   02.06.2026
* Version:    0.1
* Description: Game control module
* 
* Comments: 
*/
#include "game.h"

static int gf_allocate(char **gf, const struct game_state *gs)
/*Allocates memory for the game field lines*/
{
    int status, i;
    status = 0;
    for(i = 0; i < gs->heihgt; i++) {
        char *gf_line;
        gf_line = malloc((gs->width + 1)*sizeof(char));
        if(gf_line == NULL) {
            return ERR_MEMORY;
        }
        gf[i] = gf_line;
    }
    gf[gs->heihgt]= NULL;
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
    for(i = 0; i < gs->heihgt; i++) {
        for(j = 0; j < gs->width; j++) {
            gf[i][j] = 1;
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
    gf[gs->py][gs->px] = 2;
}

static void init_gs(struct game_state *gs, const struct window_state *ws)
/*Initializes the game state*/
{
    gs->heihgt = ws->bottom_max_y - ws->top_max_y + 1;
    gs->width = ws->right_max_x - ws->left_max_x + 1;

    gs->offset_y = ws->top_max_y;
    gs->offset_x = ws->left_max_x;

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
    if(ny >= gs->heihgt) {
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
    gf[gs->py][gs->px] = 1;
    gs->px = adjust_x(gs, nx);
    gf[gs->py][gs->px] = 2;
}

static void move_vertical(char **gf, struct game_state *gs, int ny)
/*Vertical movement of an object*/
{
    gf[gs->py][gs->px] = 1;
    gs->py = adjust_y(gs, ny);
    gf[gs->py][gs->px] = 2;
}

static void render_gf(char **gf, const struct game_state *gs)
/*Renders the game board and displays symbols according to the code*/
{
    int i, j;
    for(i = 0; i < gs->heihgt; i++) {
        for(j = 0; j < gs->width; j++) {
            if(gf[i][j] == 2) {
                move(gs->offset_y + i, gs->offset_x + j);
                addch('@');
            } else {
                move(gs->offset_y + i, gs->offset_x + j);
                addch('#');
            }
        }
    }
}

static void render_horizontal(char **gf, const struct game_state *gs, int cy)
{
    int i;
    for(i = 0; i < gs->width; i++) {
        if(gf[cy][i] == 2) {
            move(gs->offset_y + cy, gs->offset_x + i);
            addch('@');
        } else {
            move(gs->offset_y + cy, gs->offset_x + i);
            addch('?');
            }
        }
}

static void render_vertical(char **gf, const struct game_state *gs, int cx)
{
    int i;
    for(i = 0; i < gs->heihgt; i++) {
        if(gf[i][cx] == 2) {
            move(gs->offset_y + i, gs->offset_x + cx);
            addch('@');
        } else {
            move(gs->offset_y + i, gs->offset_x + cx);
            addch('?');
            }
        }
}

static void resize_gf(char ***gf, struct game_state *gs, struct window_state *ws)
{
    int status;

    gf_free(*gf);

    init_gs(gs, ws);
    *gf = malloc((gs->heihgt + 1)*sizeof(char*));
    if(*gf == NULL) {
        return;
    }
    status = init_game_field(*gf, gs);
    if(status) {
        gf_free(*gf);
        return;
    }

    init_playeryx(gs, *gf);
    render_gf(*gf, gs);
}

static void handle_key(char ***gf, struct game_state *gs, struct window_state *ws)
/*Processing keystrokes*/
{
    int key;
    while((key = getch()) != key_escape) {
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
            execute_resize(ws);
            resize_gf(gf, gs, ws);
            break;
        case key_command:
            command_process(ws);
            break;
        }
    }
}

void game_process(struct window_state *ws)
/*The main process of the game*/
{
    int status = 0;
    struct game_state gs;
    char **gf;
    init_gs(&gs, ws);

    gf = malloc((gs.heihgt + 1)*sizeof(char*));
    if(gf == NULL) {
        return;
    }
    status = init_game_field(gf, &gs);
    if(status) {
        gf_free(gf);
        return;
    }

    init_playeryx(&gs, gf);
    render_gf(gf, &gs);

    handle_key(&gf, &gs, ws);
    gf_free(gf);
}

