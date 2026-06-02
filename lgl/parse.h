#ifndef PARSE_H_SENRTY
#define PARSE_H_SENRTY

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "error.h"

#ifndef DEB
#include <curses.h>
#include "cmd.h"
#include "interface.h"
#include "state.h"
#endif

enum {key_escape = 27};
enum {key_command = '/'};
enum {buffer_size = 128};
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

#ifndef DEB

int command_process(struct window_state *ws);

#else

int DEB_command_process(char **argv);

#endif

#endif
