#ifndef PARSE_H_SENRTY
#define PARSE_H_SENRTY

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "error.h"

#ifndef DEB
#include <curses.h>
#endif

enum {buffer_size = 128};
enum {argv_number = 1};
enum {cmd_num = 2};

enum cmd_args {
    cmd, arg_1, arg_2
};

enum cmd_code {
    cmd_echo = 1,
    cmd_test = 2
};

struct cmd_state {
    int  args_count;
    enum cmd_code flag;
    char *input;
    int *lens;
    char **tickets;
};

#ifndef DEB
struct y_pos {
    int input;
    int output;
};

int command_process(int y);
#endif



#ifdef DEB
int DEB_command_process(char **argv);
#endif

#endif
