#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

enum {flags_number = 2};
enum {band_count = 4};
enum {colors_number = 12};
const char *valid_flags[] = {
    "--help",
    "--decode"
};

const char *colors[colors_number] = {
    "black", "brown", "red",
    "orange", "yellow", "green",
    "blue", "violet", "grey",
    "white", "silver", "gold"
};

enum flag_codes{
    error = -1,
    help,
    decode
};

char *allocate_color_code()
{
    return malloc(band_count*sizeof(char));
}

int parse_colors(char *color_code, char **input)
{
    int i, j, pos, flag;
    pos = 0;
    flag = 0;
    for(i = 2; i < 6; i++) {
        flag = 1;
        for(j = 0; j < colors_number; j++) {
            if(0 == my_strcmp(input[i], colors[j])) {
                color_code[pos] = j;
                pos++;
                flag = 0;
                break;
            }
        }
        if(flag) {
            return i - 1;
        }
    }
    return 0;
   
}

void decode_process(char **input)
{
    char *color_code;
    int c;
    color_code = allocate_color_code();

    c = parse_colors(color_code, input);
    if(c != 0) {
        printf("%d\n", c);
        return;
    }

    printf("%d, %d, %d, %d\n", color_code[0], color_code[1], color_code[2], color_code[3]);

    free(color_code);
}

void dispatch(enum flag_codes code, char **input)
{
    switch(code) {
    case error:
        printf("error\n");
        break;
    case help:
        printf("help\n");
        break;
    case decode:
        decode_process(input);
        break;
    }
}

int parse_arg_first(char **input){
    int i;
    for(i = 0; i < flags_number; i++) {
        if(0 == my_strcmp(input[1], valid_flags[i])) {
            return i;
        }
    }
    return -1;
}

void main_process(int argc, char **input)
{
    enum flag_codes flag_code;
    flag_code = parse_arg_first(input);
    dispatch(flag_code, input);
}

int main(int argc, char **argv)
{
    main_process(argc, argv);
    return 0;
}
