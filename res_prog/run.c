/*
* Module:     run.c
* Author:     sage
* Created:    22.05.2026
* Modified:   22.05.2026
* Version:    1.0
* Description: Main process of the program
*
* Comments:    
*/
#include "run.h"
#include "const.h"

static void print_help()
/*Prints a help*/
{
    int i;
    printf(N_("\n"));
    printf(_("Usage: res [FLAG] <color1> <color2> <color3> <color4>\n"));
    printf(N_("\n"));
    printf(_("Decode 4-band resistor color codes.\n"));
    printf(N_("\n"));
    printf(_("Flags:\n"));
    printf(_("\t--decode <color1> <color2> <color3> <color4>   Decode colors (default)\n"));
    printf(_("\t--encode soon\n"));
    printf(_("\t--help                                          Show this help\n"));
    printf(N_("\n"));
    printf(_("Valid colors:\n"));
    
    for(i = 0; i < colors_number; i++) {
        printf(N_("\t%s\n"), colors[i]);
    }
    printf(N_("\n"));
}

static void encode_process()
/*Basic encode function*/
{
    printf(_("Nothing yet\n"));
}

static void decode_process(char **input)
/*Basic decode function*/
{
    char *color_code;
    enum error_codes status;

    color_code = allocate_color_code();
    if(color_code == NULL) {
        print_error(ERR_MEMORY);
        return;
    }

    status = parse_colors(color_code, input);
    if(status) {
        print_error(status);
        return;
    }

    status = validate_colors(color_code);
    if(status) {
        print_error(status);
        return;
    }

    to_decode(color_code);

    free(color_code);
}

static void dispatch(enum flag_codes code, char **input, int argc)
/*Calls a function based on the received flag.*/
{
    switch(code) {
        case help:
            print_help();
            break;
        case decode:
            if (argc == args_number_decode) {
                decode_process(input);
            } else {
                print_error(ERR_ARRG_COUNT);
            }
            break;
        case encode:
            encode_process();
            break;
    }
}

void main_process(int argc, char **input)
/*main input processing function*/
{
    enum flag_codes flag_code;
    enum error_codes  status;

    status = check_args_number(argc);
    if(status) {
        print_error(status);
        return;
    }

    status = parse_arg_first(input, &flag_code);
    if(status) {
        print_error(status);
        return;
    }

    dispatch(flag_code, input, argc);
}
