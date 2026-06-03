#ifndef GET_H_SENTRY
#define GET_H_SENTRY

#include "state.h"

int lgl_get_std_output(struct window_state *ws);
int lgl_get_ui_top(struct window_state *ws);
int lgl_get_ui_bottom(struct window_state *ws);
int lgl_get_play_field_top(struct window_state *ws);
int lgl_get_play_field_bottom(struct window_state *ws);
int lgl_get_play_field_left(struct window_state *ws);
int lgl_get_play_field_right(struct window_state *ws);

#endif
