/*
* Module:     decode.c
* Author:     sage
* Created:    22.05.2026
* Modified:   22.05.2026
* Version:    1.0
* Description: Module for decoding color combination code
* 
* Comments:   
*/

#include "decode.h"
#include <stdio.h>

static int get_nominal(const char *color_code)
/*Calculates nominal*/
{
    return color_code[nominal_1digt]*10 + color_code[nominal_2digit];
}

static double get_multipler(const char *color_code, int *prefix)
/*Calculates multipler*/
{
   double mult;
   switch(color_code[multipler_code]) {
        case silver:
            *prefix = '\0';
            mult = 0.01;
            break;
        case gold :
            *prefix = '\0';
            mult = 0.1;
            break;
        case black:
            *prefix = '\0';
            mult = 1;
            break;
        case brown:
            *prefix = '\0';
            mult = 10;
            break;
        case red:
            *prefix = 'k';
            mult = 0.1;
            break;
        case orange:
            *prefix = 'k';
            mult = 1;
            break;
        case yellow:
            *prefix = 'k';
            mult = 10;
            break;
        case green:
            *prefix = 'm';
            mult = 0.1;
            break;
        case blue:
            *prefix = 'm';
            mult = 1;
            break;
        case violet:
            *prefix = 'm';
            mult = 10;
            break;
        case grey:
            *prefix = 'g';
            mult = 0.1;
            break;
        case white:
            *prefix = 'g';
            mult = 1;
            break;
    }
    return mult;
}

static double get_tolerance(const char *color_code)
/*Calculates tolerance*/
{
    double res;
    switch(color_code[tolerance_code]) {
        case silver:
            res = 10;
            break;
        case gold:
            res = 5;
            break;
        case brown:
            res = 1;
            break;
        case red:
            res = 2;
            break;
        case green:
            res = 0.5;
            break;
        case blue:
            res = 0.25;
            break;
        case violet:
            res = 0.1;
            break;
        case grey:
            res = 0.05;
            break;
    }
    return res;
}

static void print_decode(double resistance, double tolerance, int prefix)
/*Prints the decoding result*/
{
    printf(_("Resistor is: %g %cOhm, Tolerance %g%%\n"), resistance, prefix, tolerance);
}

void to_decode(const char *color_code)
/*The main function of decoding*/
{
    int nominal;
    double resistance, multipler, tolerance;
    int prefix;

    nominal = get_nominal(color_code);
    multipler = get_multipler(color_code, &prefix);
    tolerance = get_tolerance(color_code);
    resistance = nominal * multipler;
    print_decode(resistance, tolerance, prefix);
}
