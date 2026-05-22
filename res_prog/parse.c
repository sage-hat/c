/*
* Module:     parse.c
* Author:     sage
* Created:    22.05.2026
* Modified:   22.05.2026
* Version:    1.0
* Description: Parses input information
*
* Comments:    
*/
#include "parse.h"
#include <stdlib.h>
#include "my_string.h"

int check_args_number(int number)
/*Checks the number of arguments*/
{
    if(number == args_number_decode) {
        return 0;
    } else if(number == args_number_help) {
        return 0;
    }
    else {
        return ERR_ARRG_COUNT;
    }
}


int parse_arg_first(char **input, enum flag_codes *code)
/*Parses the first argument for flags and returns the flag number.*/
{
    int i;
    for(i = 0; i < flags_number; i++) {
        if(0 == my_strcmp(input[first_arg], valid_flags[i])) {
            *code = i;
            return 0;
        }
    }
    return ERR_INVALID_FLAG;
}

char *allocate_color_code()
/*Allocates memory for the color combination code*/
{
    return malloc(band_count*sizeof(char));
}

int parse_colors(char *color_code, char **input)
/*Basic parser for color arguments for matching*/
{
    int i, j, pos, matched;
    pos = 0;
    for(i = first_color_arg; i < last_color_arg; i++) {
        matched = 0;
        for(j = 0; j < colors_number; j++) {
            if(0 == my_strcmp(input[i], colors[j])) {
                color_code[pos] = j;
                pos++;
                matched = 1;
                break;
            }
        }
        if(!matched) {
            return ERR_COLOR;
        }
    }
    return 0;
}
