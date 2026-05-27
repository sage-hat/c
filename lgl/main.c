#include <curses.h>
#include <stdlib.h>
#include "string.h"
#include "move.h"

#ifndef DEB
static const char message[] = "@";
enum {key_escape = 27};
enum {key_command = '/'};
#endif
enum {buffer_size = 128};
enum {argv_number = 1};

enum {cmd_num = 2};
enum cmd_args {
    cmd, arg_1, arg_2
};

static const char *args[] = {
    "echo",
    "test"
};

enum cmd_code {
    cmd_echo = 1,
    cmd_test = 2
};

static char *input_allocate()
{
    char *p = malloc(buffer_size*sizeof(char));
    if(p == NULL) {
        exit(1);
    }
    return p;
}

static int ticket_allocate(char **tickets, int *lens)
{
    int i;
    char *temp;
    for(i = 0; lens[i] != '\0'; i++) {
        temp = malloc((lens[i] + 1)*(sizeof(char)));
        if(temp == NULL) {
            return 1;
        }

        tickets[i] = temp;
        temp = NULL;
    }
    tickets[i+1] = NULL;
    return 0;
}


static void normalize_input(char *input)
{
    int i,temp_count, in_spase;
    char *temp;
    temp = input_allocate();
    in_spase = 0;
    temp_count = 0;

    for(i = 0; input[i] != '\0'; i++) {
        if(input[i] != ' ') {
            temp[temp_count] = input[i];
            in_spase = 0;
            temp_count++;
        }
        else if(!in_spase) {
            temp[temp_count] = ' ';
            in_spase = 1;
            temp_count++;
        }
    }

    if((temp_count > 0) && (temp[temp_count - 1] == ' ')) {
        temp[temp_count - 1] = '\0';
    }
    else
        temp[temp_count] = '\0';
    
    strcpy(input, temp);
    free(temp);
}

static int count_args(const char* input)
{
    int i,res;
    res = 0;
    for(i = 0; input[i] != '\0'; i++) {
        if(input[i] == ' ') {
            res++;
        }
    }
    return ++res;
}

static void analyze_input(int *res, char *input, int args)
{
    int pos, i, cur_arg;
    cur_arg = 0;
    pos = 0;
    for(i = 0; input[i] != '\0'; i++) {
        if(input[i] != ' ') {
            cur_arg++;
        }
        else {
            res[pos] = cur_arg;
            cur_arg = 0;
            pos++;
        }
    }
    res[pos] = cur_arg;
    res[pos + 1] = '\0';
}

static void split_input(char **tickets, char *input)
{
    int i, tick_count, str_pos;
    tick_count = 0;
    str_pos = 0;
    for(i = 0; input[i] != '\0'; i++) {
        if(input[i] == ' ') {
            tickets[tick_count][str_pos] = '\0';
            tick_count++;
            str_pos = 0;
        }
        else {
            tickets[tick_count][str_pos] = input[i];
            str_pos++;
        }
    }
    tickets[tick_count][str_pos] = '\0';
}

static int check_cmd(char **tickets, enum cmd_code *flag)
{
    int status, i;
    for(i = 0; i < cmd_num; i++) {
        if(0 == strcmp(tickets[cmd], args[i])) {
            *flag = i + 1;
            status = 0;
            break;
        }
        else {
            status = 1;
        }
    }
    return status;
}

static void cmd_dispatcher(enum cmd_code flag, char **tickets)
{
    switch(flag) {
        case cmd_echo:
            printf("%s\n", tickets[arg_1]);
            break;
        case cmd_test:
            printf("It's just a test command\n");
            break;
    }
}

#ifndef DEB
static int read_chars(char *input)
{
    int c;
    int i = 0;
    while((c = getch()) != '\n'){
        if(i < buffer_size) {
            input[i] = c;
            i++;
        }
        else 
            return -1;
    }
    input[i] = '\0';
    return 0;
}

static void clear_line(int y)
{
    int i;
    for(i = 0; i < 50; i++) {
        move(y, i);
        addch(' ');
    }
}

static void command_process(int y)
{
    int status, outp_y, inp_y;
    char *input;

    input = input_allocate();
    inp_y = y-1;
    outp_y = inp_y - 1;

    clear_line(outp_y);

    move(inp_y, 0);
    addch('/');
    move(inp_y, 1);
    echo();
    
    status = read_chars(input);
    if(status) {
        exit(1);
    }
    normalize_input(input);

    clear_line(inp_y);

    move(outp_y, 0);
    addstr(input);
    free(input);
    noecho();
}
#else

static int DEB_read_chars(char *input, char *arg)
{
    int i;

    if(arg == NULL) {
        return 1;
    }

    for(i = 0; arg[i] != '\0'; i++) {
        if(i < buffer_size) {
            input[i] = arg[i];
        }
        else 
            return -1;
    }
    input[i] = '\0';
    return 0;
}

static void DEB_command_process(char **argv)
{
    int status, args_count;
    enum cmd_code flag;
    char *input;
    int *lens;
    char **tickets;

    input = input_allocate();
    status = DEB_read_chars(input, argv[argv_number]);
    if(status == 1) {
        printf("Needs arguments\n");
        exit(1);
    }
    if(status == -1) {
        exit(1);
    }

    normalize_input(input);
    args_count = count_args(input);

    lens = malloc((args_count + 1)*sizeof(int));
    if(lens == NULL) {
        exit(1);
    }

    analyze_input(lens, input, args_count);

    tickets = malloc((args_count + 1)*sizeof(char*));
    if(tickets == NULL) {
        exit(1);
    }

    status = ticket_allocate(tickets, lens);
    if(status) {
        exit(1);
    }

    split_input(tickets, input);

    free(input);
    free(lens);

    status = check_cmd(tickets, &flag);
    if(status) {
        printf("error\n");
        return;
    }

    cmd_dispatcher(flag, tickets);
}
#endif
int main(int argc, char **argv)
{
#ifndef DEB
    int row, col, x, y, max_x, max_y, key;
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    getmaxyx(stdscr, row, col);
    x = (col -(sizeof(message)-1)) / 2;
    y = row/2;
    max_x = col - sizeof(message) + 1;
    max_y = row - 1;
    show_message(x, y);
    while((key = getch()) != key_escape) {
        switch(key) {
        case KEY_UP:
            move_message(&x, &y, max_x, max_y, 0, -1);
            break;
        case KEY_DOWN:
            move_message(&x, &y, max_x, max_y, 0, 1);
            break;
            case KEY_LEFT:
            move_message(&x, &y, max_x, max_y, -1, 0);
            break;
        case KEY_RIGHT:
            move_message(&x, &y, max_x, max_y, 1, 0);
            break;
        case KEY_RESIZE:
            handle_resize(&x, &y, &max_x, &max_y);
            break;
        case key_command:
            command_process(max_y);
            break;
        }
    }
    endwin();
    return 0;
#else
    DEB_command_process(argv);
    return 0;
#endif
}
