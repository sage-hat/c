/*
* Module:     error.c
* Author:     sage
* Created:    28.05.2026
* Modified:   02.06.2026
* Version:    0.1
* Description: Error handling module
* 
* Comments:   
*/
#include "error.h"

/*--==List of error messages==-- */
static const char *ERR_START = {_("Error %d: %s")};
static const char *ERR_MEMORY_MSG = {_("Memory allocation failed")};
static const char *ERR_BUFFER_OVERFLOW_MSG = {_("Buffer overflow - input too long")};
static const char *ERR_UNKNOWN_COMMAND_MSG = {_("Unknown command")};
static const char *ERR_UNKNOWN_ARG_MSG = {_("Unknown argument")};
static const char *ERR_WRONG_ARGS_COUNT_MSG = {_("Incorrect number of arguments entered")};


#ifndef DEB
void errprint(enum errors err_code, int output)
/*Prints an error message according to the received error code.*/
{
    switch(err_code) {
        case ERR_MEMORY:
            mvprintw(output, 0, ERR_START, err_code, ERR_MEMORY_MSG);
            refresh();
            break;
        case ERR_BUFFER_OVERFLOW:
            mvprintw(output, 0, ERR_START, err_code, ERR_BUFFER_OVERFLOW_MSG);
            refresh();
            break;
        case ERR_UNKNOWN_COMMAND:
            mvprintw(output, 0, ERR_START, err_code, ERR_UNKNOWN_COMMAND_MSG);
            refresh();
            break;
        case ERR_UNKNOWN_ARG:
            mvprintw(output, 0, ERR_START, err_code, ERR_UNKNOWN_ARG_MSG);
            refresh();
            break;
        case ERR_WRONG_ARGS_COUNT:
            mvprintw(output, 0, ERR_START, err_code, ERR_WRONG_ARGS_COUNT_MSG);
            refresh();
            break;

    }
}
#else

void DEB_errprint(enum errors err_code)
/* =For debugging= Prints an error message according to the received error code.*/
{
    
    switch(err_code) {
        case ERR_MEMORY:
            fprintf(stderr, _("Error %d: %s\n"), err_code, ERR_MEMORY_MSG);
            break;
        case ERR_BUFFER_OVERFLOW:
            fprintf(stderr, _("Error %d: %s\n"), err_code, ERR_BUFFER_OVERFLOW_MSG);
            break;
        case ERR_UNKNOWN_COMMAND:
            fprintf(stderr, _("Error %d: %s\n"), err_code, ERR_UNKNOWN_COMMAND_MSG);
            break;
    }
}

#endif
