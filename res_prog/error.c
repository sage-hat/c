/*
* Module:     error.c
* Author:     sage
* Created:    22.05.2026
* Modified:   22.05.2026
* Version:    1.0
* Description: Error handling module
* 
* Comments:   
*/
#include "const.h"
#include "error.h"
#include <stdio.h>

void print_error(enum error_codes code)
/*Prints an error message according to the received error code.*/
{
    switch(code) {
        case ERR_ARRG_COUNT:
            printf(_("Error %d: Invalid number of arguments\n"), code);
            break;
        case ERR_INVALID_FLAG:
            printf(_("Error %d: Invalid flag\n"), code);
            break;
        case ERR_MEMORY:
            printf(_("Error %d: Memory allocation error\n"), code);
            break;
        case ERR_COLOR:
            printf(_("Error %d: Invalid color entered, use --help to get a list of available colors\n"), code);
            break;
        case ERR_FARG_1:
            printf(_("Error %d: first argument cannot be \"black\"\n"), code);
            break;
        case ERR_NOMINAL_SILVER:
            printf(_("Error %d: Nominal cannot be \"silver\"\n"), code);
            break;
        case ERR_NOMINAL_GOLD:
            printf(_("Error %d: Nominal cannot be \"gold\"\n"), code);
            break;
        case ERR_TOL_1:
            printf(_("Error %d: Tolerance cannot be \"black\"\n"), code);
            break;
        case ERR_TOL_2:
            printf(_("Error %d: Tolerance cannot be \"orange\"\n"), code);
            break;
        case ERR_TOL_3:
            printf(_("Error %d: Tolerance cannot be \"yellow\"\n"), code);
            break;
        case ERR_TOL_4:
            printf(_("Error %d: Tolerance cannot be \"white\"\n"), code);
            break;
    }
}
