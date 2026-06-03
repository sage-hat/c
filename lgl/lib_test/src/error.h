#ifndef ERROR_H_SENTRY
#define ERROR_H_SENTRY

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

#include <stdio.h>
#include <curses.h>

enum errors {
    ERR_MEMORY = 1,
    ERR_BUFFER_OVERFLOW,
    ERR_UNKNOWN_COMMAND,
    ERR_UNKNOWN_ARG,
    ERR_WRONG_ARGS_COUNT
};

void errprint(enum errors err_code, int output);

#endif

