/*
* Module:     valid.c
* Author:     sage
* Created:    22.05.2026
* Modified:   22.05.2026
* Version:    1.0
* Description: Validates the color combination code according to the rules
*
* Comments:    
*/
#include "valid.h"
#include "const.h"


static int check_first_code(enum colors_code code)
/*Validates the first color code*/
{
    switch(code) {
        case black:
            return(ERR_FARG_1);
            break;
        case silver:
            return(ERR_NOMINAL_SILVER);
            break;
        case gold:
            return(ERR_NOMINAL_GOLD);
            break;
        default:
            return 0;
    }
}

static int check_second_code(enum colors_code code)
/*Validates the second color code*/
{
    switch(code) {
        case silver:
            return(ERR_NOMINAL_SILVER);
            break;
        case gold:
            return(ERR_NOMINAL_GOLD);
            break;
        default:
            return 0;
    }
}

static int check_third_code(enum colors_code code)
/*Validates the third color code*/
/*Can be any color from the range*/
{
    return 0;
}

static int check_fourth_code(enum colors_code code)
/*Validates the fourth color code*/
{
    switch(code) {
        case black:
            return(ERR_TOL_1);
            break;
        case orange:
            return(ERR_TOL_2);
            break;
        case yellow:
            return(ERR_TOL_3);
            break;
        case white:
            return(ERR_TOL_4);
            break;
        default:
            return 0;
    }
}

int validate_colors(const char *raw_code)
/*The main validation function. Checks each code for correctness.*/
{
    enum error_codes status;
    enum range{code_1, code_2, code_3, code_4};
    enum colors_code current_code;
    int i;

    for(i = 0; i < band_count; i++ ) {
        current_code = raw_code[i];
        switch(i) {
            case code_1:
                status = check_first_code(current_code);
                if(status) {
                    return status;
                }
                break;
            case code_2:
                status = check_second_code(current_code);
                if(status) {
                    return status;
                }
                break;
            case code_3:
                status = check_third_code(current_code);
                if(status) {
                    return status;
                }
                break;
            case code_4:
                status = check_fourth_code(current_code);
                if(status) {
                    return status;
                }
                break;
            default:
                status = 0;
        }
    }
    return status;
}
