#ifndef CMD_H_SENTRY
#define CMD_H_SENTRY

#include <curses.h>
#include "state.h"
#include "interface.h"
enum cmd_args {
    cmd, arg_1, arg_2
};

enum cmd_code {
    cmd_echo = 1,
    cmd_print,
    cmd_clear,
    cmd_exit,
    cmd_refresh
};

enum cmd_args_name {
    arg_std = 1,
    arg_uit,
    arg_uib
};

void cmd_dispatcher(enum cmd_code flag, char **tickets, const struct window_state *ws);
#endif
