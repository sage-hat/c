/*
* Module:     error.c
* Author:     sage
* Created:    28.05.2026
* Modified:   28.05.2026
* Version:    1.0
* Description: Error handling module
* 
* Comments:   
*/
#include "error.h"

/*--==List of error messages==-- */
static const char *ERR_MEMORY_MSG = {_("Memory allocation failed")};
static const char *ERR_BUFFER_OVERFLOW_MSG = {_("Buffer overflow - input too long")};
static const char *ERR_UNKNOWN_COMMAND_MSG = {_("Unknown command")};


#ifndef DEB
void errprint(enum errors err_code, int output)
/*Prints an error message according to the received error code.*/
{
    switch(err_code) {
        case ERR_MEMORY:
            mvprintw(output, 0, _("error %d: %s"), err_code, ERR_MEMORY_MSG);
            break;
        case ERR_BUFFER_OVERFLOW:
            mvprintw(output, 0, _("error %d: %s"), err_code, ERR_BUFFER_OVERFLOW_MSG);
            break;
        case ERR_UNKNOWN_COMMAND:
            mvprintw(output, 0, _("error %d: %s"), err_code, ERR_UNKNOWN_COMMAND_MSG);
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
