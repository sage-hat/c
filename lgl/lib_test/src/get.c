#include "get.h"

int lgl_get_std_output(struct window_state *ws)
{
    return ws->std_output;
}

int lgl_get_ui_top(struct window_state *ws)
{
    return ws->ui_top;
}

int lgl_get_ui_bottom(struct window_state *ws)
{
    return ws->ui_bottom;
}

int lgl_get_play_field_top(struct window_state *ws)
{
    return ws->top_max_y;
}

int lgl_get_play_field_bottom(struct window_state *ws)
{
    return ws->bottom_max_y;
}

int lgl_get_play_field_left(struct window_state *ws)
{
    return ws->left_max_x;
}

int lgl_get_play_field_right(struct window_state *ws)
{
    return ws->right_max_x;
}

