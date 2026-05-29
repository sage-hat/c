/*
* Module:     decode.c
* Author:     sage
* Created:    28.05.2026
* Modified:   29.05.2026
* Version:    1.0
* Description: Parses input command line 
* 
* Comments:   
*/
#include "parse.h"

static const char *args[] = {
/*List of valid commands*/
    "echo",
    "test"
};

static char *input_allocate(int *status)
/*Allocates memory for the input string*/
{
    char *p = malloc(buffer_size*sizeof(char));
    if(p == NULL) {
        *status = ERR_MEMORY;
        return NULL;
    }
    *status = 0;
    return p;
}

static int ticket_allocate(char **tickets, int *lens)
/*Allocates memory for an array of tickets*/
{
    int i;
    char *temp;
    for(i = 0; lens[i] != '\0'; i++) {
        temp = malloc((lens[i] + 1)*(sizeof(char)));
        if(temp == NULL) {
            return ERR_MEMORY;
        }

        tickets[i] = temp;
        temp = NULL;
    }
    tickets[i] = NULL;
    return 0;
}

static void tickets_free(char **tickets)
/*Frees up the memory of the array with tickets*/
{
    int i;
    for(i = 0; tickets[i] != NULL; i++) {
        free(tickets[i]);
    }
    free(tickets);
}

static int normalize_input(char *input)
/*Normalizes the input string*/
{
    int i, temp_count, in_space;
    int status = 0;
    char *temp;

    temp = input_allocate(&status);
    if(status) {
        return status;
    }

    in_space = 0;
    temp_count = 0;

    for(i = 0; input[i] != '\0'; i++) {
        if(input[i] != ' ') {
            temp[temp_count] = input[i];
            in_space = 0;
            temp_count++;
        }
        else if(!in_space) {
            temp[temp_count] = ' ';
            in_space = 1;
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
    return 0;
}

static int count_args(const char* input)
/*Counts argsuments of the input string*/
{
    int i,res;
    res = 0;
    for(i = 0; input[i] != '\0'; i++) {
        if(input[i] == ' ') {
            res++;
        }
    }
    if(i == 0 && res == 0) {
        return res;
    }
    return ++res;
}

static void analyze_input(int *res, char *input)
/*Counts the number of characters in each argument*/
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
/*Splits a string into tickets*/
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
/*Checks if the first ticket is a valid command*/
{
    int status, i;
    for(i = 0; i < cmd_num; i++) {
        if(0 == strcmp(tickets[cmd], args[i])) {
            *flag = i + 1;
            status = 0;
            break;
        }
        else {
            status = ERR_UNKNOWN_COMMAND;
        }
    }
    return status;
}

static void cmd_dispatcher(enum cmd_code flag, char **tickets, int output)
/*The process of calling functions depending on the received command code*/
{
    switch(flag) {
        case cmd_echo:
            mvprintw(output, 0, "%s", tickets[arg_1]);
            break;
        case cmd_test:
            mvprintw(output, 0, "It's just a test command");
            break;
    }
}

#ifndef DEB
static void handle_backspace(int y, int *i)
/*Handles the case of backspace input*/
{
    int pos;
    pos = *i;
    if(pos < 1) {
        pos = 1;
        move(y, pos);
        addch(' ');
        move(y, pos);
        *i = 0;
    }
    else {
        move(y, pos);
        addch(' ');
        move(y, pos);
        (*i)--;
    }

}
static int read_chars(char *input, int y)
/* Fills a string with characters*/
{
    int c;
    int i = 0;
    while((c = getch()) != '\n'){
        if(i < buffer_size) {
            if(i == 0 && c == key_command) {
                /*Allows you to close a line with a slash character
                 * if nothing is entered*/
                return status_slash;
            }
            if(c == KEY_BACKSPACE) {
                handle_backspace(y, &i);
           } 
            else {
                input[i] = c;
                i++;
            }
        }
        else 
            return ERR_BUFFER_OVERFLOW;
    }
    input[i] = '\0';
    return 0;
}

static void clear_line(int y, int x)
/*Clears the line at the specified y*/
{
    int i;
    for(i = 0; i <= x; i++) {
        move(y, i);
        addch(' ');
    }
    refresh();
}

static int parse_cmd(struct cmd_state *cmd, const struct window_state *ws)
/*String parsing process*/
{ 
    int status = 0;
    cmd->input = input_allocate(&status);
    if(status) {
        errprint(status, ws->cmd_output);
        clear_line(ws->cmd_input, ws->max_x);
        return status;
    }

    status = read_chars(cmd->input, ws->cmd_input);
    if(status < 0) {
        free(cmd->input);
        return -1;
    }
    if(status > 0) {
        errprint(status, ws->cmd_output);
        clear_line(ws->cmd_input, ws->max_x);
        free(cmd->input);
        return status;
    }

    status = normalize_input(cmd->input);
    if(status) {
        errprint(status, ws->cmd_output);
        clear_line(ws->cmd_input, ws->max_x);
        free(cmd->input);
        return status;

    }

    cmd->args_count = count_args(cmd->input);
    if(cmd->args_count == 0) {
        /*If nothing is entered, pressing space closes the input*/
        free(cmd->input);
        return status_empty_str;
    }

    cmd->lens = malloc((cmd->args_count + 1)*sizeof(int));
    if(cmd->lens == NULL) {
        errprint(ERR_MEMORY, ws->cmd_output);
        clear_line(ws->cmd_input, ws->max_x);
        free(cmd->input);
        return ERR_MEMORY;
    }

    analyze_input(cmd->lens, cmd->input);

    cmd->tickets = malloc((cmd->args_count + 1)*sizeof(char*));
    if(cmd->tickets == NULL) {
        errprint(ERR_MEMORY, ws->cmd_output);
        clear_line(ws->cmd_input, ws->max_x);
        free(cmd->lens);
        free(cmd->input);
        return ERR_MEMORY;
    }

    status = ticket_allocate(cmd->tickets, cmd->lens);
    if(status) {
        errprint(status, ws->cmd_output);
        clear_line(ws->cmd_input, ws->max_x);
        free(cmd->tickets);
        free(cmd->lens);
        free(cmd->input);
        return status;
    }

    split_input(cmd->tickets, cmd->input);

    free(cmd->input);
    free(cmd->lens);

    status = check_cmd(cmd->tickets, &cmd->flag);
    if(status) {
        errprint(status, ws->cmd_output);
        clear_line(ws->cmd_input, ws->max_x);
        tickets_free(cmd->tickets);
        return status;
    }
    return status;
}
/*
static void init_cmd_pos(int y, struct y_pos *cmd_y)
Sets the values of y for command line input and output.
{
    cmd_y->input = y;
    cmd_y->output = cmd_y->input - 1;

}
*/
static void start_cmd(int y)
/*Outputs the command line character*/
{
    move(y, 0);
    addch(key_command);
    move(y, 1);
    echo();
    refresh();
}

int command_process(struct window_state *ws)
/*Fills a string with characters*/
{
    int status = 0;
    struct cmd_state cmd;
    
    clear_line(ws->cmd_output, ws->max_x);

    start_cmd(ws->cmd_input);
    
    status = parse_cmd(&cmd, ws);
    if(status == 0) {
        cmd_dispatcher(cmd.flag, cmd.tickets, ws->cmd_output);
        tickets_free(cmd.tickets);
    }
    

    clear_line(ws->cmd_input, ws->max_x);
    noecho();
    curs_set(0);
    refresh();

    return status;
}

#else

static int DEB_read_chars(char *input, char *arg)
/* =For debugging= Fills a string with characters*/
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
            return ERR_BUFFER_OVERFLOW;
    }
    input[i] = '\0';
    return 0;
}

static void DEB_cmd_dispatcher(enum cmd_code flag, char **tickets)
/*The process of calling functions depending on the received command code*/
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

int DEB_command_process(char **argv)
/* =For debugging= The main command line process*/
{
    struct cmd_state cmd;
    int status = 0;

    cmd.input = input_allocate(&status);
    if(status) {
        DEB_errprint(status);
        return status;
    }

    status = DEB_read_chars(cmd.input, argv[argv_number]);
    if(status) {
        DEB_errprint(status);
        return status;
    }

    status = normalize_input(cmd.input);
    if(status) {
        DEB_errprint(status);
        return status;
    }

    cmd.args_count = count_args(cmd.input);

    cmd.lens = malloc((cmd.args_count + 1)*sizeof(int));
    if(cmd.lens == NULL) {
        DEB_errprint(ERR_MEMORY);
        return ERR_MEMORY;
    }

    analyze_input(cmd.lens, cmd.input);

    cmd.tickets = malloc((cmd.args_count + 1)*sizeof(char*));
    if(cmd.tickets == NULL) {
        DEB_errprint(ERR_MEMORY);
        return ERR_MEMORY;
    }

    status = ticket_allocate(cmd.tickets, cmd.lens);
    if(status) {
        DEB_errprint(status);
        return status;
    }

    split_input(cmd.tickets, cmd.input);

    free(cmd.input);
    free(cmd.lens);

    status = check_cmd(cmd.tickets, &cmd.flag);
    if(status) {
        DEB_errprint(status);
        return status;
    }

    DEB_cmd_dispatcher(cmd.flag, cmd.tickets);
    
    tickets_free(cmd.tickets);
    return 0;
}
#endif
