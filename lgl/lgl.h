#ifndef LGL_H_SENTRY
#define LGL_H_SENTRY

#include "state.h"

int command_process(struct window_state *ws);
void init_window(struct window_state *ws);

void clear_line(int y, int x);
#endif
