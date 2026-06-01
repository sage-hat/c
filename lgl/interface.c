#include "interface.h"

static const char message[] = "@";
static const char h_char[] = "-";
static const char v_char[] = "|";
static const char corner_char[] = "O";
static const char clear_char[] = " ";

void init_game(struct window_state *ws, int *x, int *y)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    *x = (col -(sizeof(message)-1)) / 2;
    *y = row/2;
    ws->max_x = col - sizeof(message) + 1;
    ws->max_y = row - 1;
    set_win_coords(ws);
    show_message(*x, *y);

    set_border(ws);

    refresh();
}

void execute_resize(struct window_state *ws, int *x, int *y)
{
    clear_border(ws);
    handle_resize(x, y, ws);
    set_win_coords(ws);
    set_border(ws);
}


void clear_line(int y, int x)
/*Clears the line at the specified y*/
{
    int i;
    for(i = 0; i <= x; i++) {
        move(y, i);
        addch(' ');
    }
    refresh();
}
static void init_cmd_pos(struct window_state *ws)
/*Sets the values of y for command line input and output.*/
{
    ws->cmd_input = ws->max_y;
    ws->cmd_output = ws->cmd_input - 1;
}

static void init_top(struct window_state *ws)
{
    ws->ui_top = 0;
    ws->ui_bottom = ws->ui_top + 1;
    ws->top_border = ws->ui_bottom + 1;
    ws->top_max_y = ws->top_border + 1;
}

static void init_bottom(struct window_state *ws)
{
    ws->std_output = ws->cmd_output - 1;
    ws->bottom_border = ws->std_output - 1;
    ws->bottom_max_y = ws->bottom_border - 1;
}

static void init_borders(struct window_state *ws)
{
    ws->left_border_x = 1;
    ws->left_max_x = ws->left_border_x + 1;
    ws->right_border_x = ws->max_x - 1;
    ws->right_max_x = ws->right_border_x - 1;
}

static void render_border
        (int start_pos, int finish_pos, int static_pos, enum render_mode mode)
{
    int i;
    for(i = start_pos; i < finish_pos; i++) {
        switch(mode) {
            case h_print:
                move(static_pos, i);
                addstr(h_char);
                break;
            case v_print:
                move(i, static_pos);
                addstr(v_char);
                break;
            case h_clear:
                move(static_pos, i);
                addstr(clear_char);
                break;
            case v_clear:
                move(i, static_pos);
                addstr(clear_char);
                break;
        }
    }
}

static void draw_corners(int y, int x_1, int x_2)
{
    move(y, x_1);
    addstr(corner_char);
    move(y, x_2);
    addstr(corner_char);
 
}

void set_border(const struct window_state *ws)
{
    render_border(ws->left_border_x, ws->right_border_x, ws->top_border, h_print);
    render_border(ws->left_border_x, ws->right_border_x, ws->bottom_border, h_print);
    render_border(ws->top_border, ws->bottom_border, ws->left_border_x, v_print);
    render_border(ws->top_border, ws->bottom_border, ws->right_border_x, v_print);

    draw_corners(ws->top_border, ws->left_border_x, ws->right_border_x);
    draw_corners(ws->bottom_border, ws->left_border_x, ws->right_border_x);
    refresh();
}

void clear_border(const struct window_state *ws)
{
    render_border(ws->left_border_x, ws->right_border_x, ws->top_border, h_clear);
    render_border(ws->left_border_x, ws->right_border_x, ws->bottom_border, h_clear);
    render_border(ws->top_border, ws->bottom_border, ws->left_border_x, v_clear);
    render_border(ws->top_border, ws->bottom_border, ws->right_border_x, v_clear);
    refresh();
}

void set_win_coords(struct window_state *ws)
{
    init_cmd_pos(ws);
    init_top(ws);
    init_bottom(ws);
    init_borders(ws);
}
