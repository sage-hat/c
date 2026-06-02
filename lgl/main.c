#include <curses.h>
#include <stdlib.h>
#include "string.h"
#include "move.h"
#include "parse.h"
#include "interface.h"

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

#ifndef DEB

static int gf_allocate(char **gf, int my, int mx)
{
    int status, i;
    status = 0;
    for(i = 0; i != my + 1; i++) {
        char *gf_line;
        gf_line = malloc((mx + 1)*sizeof(char));
        if(gf_line == NULL) {
            return ERR_MEMORY;
        }
        gf[i] = gf_line;
    }
    gf[i]= NULL;
    return status;
}

static void gf_free(char **gf)
/*Frees up the memory of the array with tickets*/
{
    int i;
    for(i = 0; gf[i] != NULL; i++) {
        free(gf[i]);
    }
    free(gf);
}

static void set_gf(char **gf, int mx)
{
    int i, j;
    for(i = 0; gf[i] != NULL; i++) {
        for(j = 0; j != mx + 1; j++) {
            gf[i][j] = 1;
        }
        gf[i][j] = '\0';
    }
}

static void render_gf(char **gf, int my, int mx)
{
    int i, j;
    for(i = my; gf[i] != NULL; i++) {
        for(j = mx; gf[i][j] != '\0'; j++) {
            if(gf[i][j] == 2) {
                move(i, j);
                addch('#');
            } else {
                move(i, j);
                addch(' ');
            }
        }
    }
}


static int init_game_field(char **gf, const struct game_state *gs)
{
    int status = 0;
    
    status = gf_allocate(gf, gs->max_y, gs->max_x);
    if(status) {
        return status;
    }
    set_gf(gf, gs->max_x);

    return status;
}

static void init__game(struct game_state *gs)
{
    gs->py = gs->min_y;
    gs->px = gs->min_x;
}

static int adjust_x(const struct game_state *gs, int nx)
{
    if(nx > gs->max_x) {
        return gs->max_x;
    } else if(nx < gs->min_x) {
        return gs->min_x;
    } else {
        return nx;
    }

}

static int adjust_y(const struct game_state *gs, int ny)
{
    if(ny > gs->max_y) {
        return gs->max_y;
    } else if(ny < gs->min_y) {
        return gs->min_y;
    } else {
        return ny;
    }

}

static void move_horizontal(char **gf, struct game_state *gs, int nx)
{
    gf[gs->py][gs->px] = 1;
    gs->px = adjust_x(gs, nx);
    gf[gs->py][gs->px] = 2;
}

static void move_vertical(char **gf, struct game_state *gs, int ny)
{
    gf[gs->py][gs->px] = 1;
    gs->py = adjust_y(gs, ny);
    gf[gs->py][gs->px] = 2;
}

static void game_process()
{
    int status = 0;
    struct window_state ws;
    struct game_state gs;
    char **gf;

    int x, y, key;
    x = 0;
    y = 0;
    
    init_game(&ws, &x, &y);

    gs.min_y = ws.top_max_y;
    gs.max_y = ws.bottom_max_y;
    gs.min_x = ws.left_max_x;
    gs.max_x = ws.right_max_x;


    gf = malloc((gs.max_y + 1)*sizeof(char*));
    if(gf == NULL) {
        return;
    }

    status = init_game_field(gf, &gs);
    if(status) {
        gf_free(gf);
        return;
    }

    init__game(&gs);
    gf[gs.py][gs.px] = 2;

    render_gf(gf, gs.min_y, gs.min_x);

    while((key = getch()) != key_escape) {
        switch(key) {
        case KEY_UP:
            move_message(&x, &y, &ws, 0, -1);
            move_vertical(gf, &gs, gs.py - 1);
            render_gf(gf, gs.min_y, gs.min_x);
            break;
        case KEY_DOWN:
            move_message(&x, &y, &ws, 0, 1);
            move_vertical(gf, &gs, gs.py + 1);
            render_gf(gf, gs.min_y, gs.min_x);
            break;
            case KEY_LEFT:
            move_message(&x, &y, &ws, -1, 0);
            move_horizontal(gf, &gs, gs.px - 1);
            render_gf(gf, gs.min_y, gs.min_x);
            break;
        case KEY_RIGHT:
            move_message(&x, &y, &ws, 1, 0);
            move_horizontal(gf, &gs, gs.px + 1);
            render_gf(gf, gs.min_y, gs.min_x);
            break;
        case KEY_RESIZE:
            execute_resize(&ws, &x, &y);
            break;
        case key_command:
            status = command_process(&ws);
            break;
        }
    }

    gf_free(gf);
    endwin();
}

int main()
{
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);

    game_process();
   
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

