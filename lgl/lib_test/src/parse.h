#ifndef PARSE_H_SENRTY
#define PARSE_H_SENRTY

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include "lgl_priv.h"
#include "cmd.h"
/*
#include "error.h"
#include "interface.h"
#include "state.h"
*/
enum {argv_number = 1};
enum {cmd_num = 5};
enum {args_num = 3};

enum stat_code {
    status_slash = -1,
    status_empty_str = -2,
    status_need_check_arg = -3
};

enum {
    args_one = 1,
    args_two,
    args_three
};

struct cmd_state {
    int  args_count;
    enum cmd_code flag;
    enum cmd_args_name arg;
    char *input;
    int *lens;
    char **tickets;
};


int lgl_command_process(struct window_state *ws);

#endif

