#include <stdio.h>
#include "my_string.h"

enum {flags_number = 2};

const char *valid_flags[] = {
    "--help",
    "--decode"
};

enum flag_codes{
    error = -1,
    help,
    decode
};

void handle_flag(enum flag_codes code)
{
    switch(code) {
    case error:
        printf("error\n");
        break;
    case help:
        printf("help\n");
        break;
    case decode:
        printf("decode\n");
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

void parse_arg(int argc, char **argv)
{
    enum flag_codes flag_code;
    
    flag_code = parse_arg_first(argv);

    handle_flag(flag_code);
}

int main(int argc, char **argv)
{
    parse_arg(argc, argv);
    return 0;
}
