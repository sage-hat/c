#ifndef PARSE_H_SENTRY
#define PARSE_H_SENTRY

#include "const.h"

int check_args_number(int number);

int parse_arg_first(char **input, enum flag_codes *code);

char *allocate_color_code();

int parse_colors(char *color_code, char **input);

#endif
