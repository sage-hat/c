#ifndef ERROR_H_SENTRY
#define ERROR_H_SENTRY

#include <stdio.h>

#ifndef DEB
#include <curses.h>
#endif

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/


enum errors {
    ERR_MEMORY = 1,
    ERR_BUFFER_OVERFLOW,
    ERR_UNKNOWN_COMMAND
};


#ifndef DEB
void errprint(enum errors err_code, int output);
#else
/* Debug errors print */
void DEB_errprint(enum errors err_code);
#endif


#endif
