/*
* Module:     decode.c
* Author:     sage
* Created:    28.05.2026
* Modified:   03.06.2026
* Version:    0.1
* Description: Parses input command line 
* 
* Comments: Debug mode is not relevant
*/

#include "parse.h"

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
        if(0 == strcmp(tickets[cmd], commands[i])) {
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

static int check_args_count(struct cmd_state *cmd)
/*Checks the flag against the argument count condition*/
{
    int status = 0;
    enum cmd_code flag_code;
    flag_code = cmd->flag;
    switch(flag_code) {
        case cmd_echo:
            if(cmd->args_count == args_two) {
                status = 0;
            } else {
                status = ERR_WRONG_ARGS_COUNT;
            }
            break;
        case cmd_print:
            if(cmd->args_count == args_three) {
                status = status_need_check_arg;
            } else {
                status = ERR_WRONG_ARGS_COUNT;
            }
            break;
        case cmd_clear:
            if(cmd->args_count == args_two) {
                status = status_need_check_arg;
            } else {
                status = ERR_WRONG_ARGS_COUNT;
            }
            break;
        case cmd_exit:
            if(cmd->args_count == args_one) {
                status = 0;
            } else {
                status = ERR_WRONG_ARGS_COUNT;
            }
            break;
        case cmd_refresh:
            if(cmd->args_count == args_one) {
                status = 0;
            } else {
                status = ERR_WRONG_ARGS_COUNT;
            }
            break;
    }
    return status;
}

static int check_arg(char **tickets, enum cmd_args_name *arg, int args_count)
/*Checks if the second ticket is a valid argumen*/
{
    int i, status, curent_arg;
    if(args_count < 2) {
        return ERR_WRONG_ARGS_COUNT;
    }
    for(i = 0; i < args_num; i++) {
        if(0 == strcmp(tickets[arg_1], arguments[i])){
            curent_arg = i + 1;
            status = 0;
            break;
        } else {
            status = ERR_UNKNOWN_ARG;
        }
    }
    *arg = curent_arg;
    
    return status;
}

static int valid_args(struct cmd_state *cmd)
/*Command line argument validation process*/
{
    int status = 0;
    status = check_cmd(cmd->tickets, &cmd->flag);
    if(status) {
        return status;
    }
    status = check_args_count(cmd);
    if(status > 0) {
        return status;
    }
    if(status == status_need_check_arg) {
        status = check_arg(cmd->tickets, &cmd->arg, cmd->args_count);
        if(status) {
            return status;
        }
    }
    return status;
}

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
            if(i == 0 && c == lgl_key_command) {
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

static int parse_cmd(struct cmd_state *cmd, const struct window_state *ws)
/*String parsing process*/
{ 
    int status = 0;
    cmd->input = input_allocate(&status);
    if(status) {
        errprint(status, ws->cmd_output);
        lgl_clear_line(ws->cmd_input, ws->max_x);
        return status;
    }

    status = read_chars(cmd->input, ws->cmd_input);
    if(status < 0) {
        free(cmd->input);
        return status_slash;
    }
    if(status > 0) {
        errprint(status, ws->cmd_output);
        lgl_clear_line(ws->cmd_input, ws->max_x);
        free(cmd->input);
        return status;
    }

    status = normalize_input(cmd->input);
    if(status) {
        errprint(status, ws->cmd_output);
        lgl_clear_line(ws->cmd_input, ws->max_x);
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
        lgl_clear_line(ws->cmd_input, ws->max_x);
        free(cmd->input);
        return ERR_MEMORY;
    }

    analyze_input(cmd->lens, cmd->input);

    cmd->tickets = malloc((cmd->args_count + 1)*sizeof(char*));
    if(cmd->tickets == NULL) {
        errprint(ERR_MEMORY, ws->cmd_output);
        lgl_clear_line(ws->cmd_input, ws->max_x);
        free(cmd->lens);
        free(cmd->input);
        return ERR_MEMORY;
    }

    status = ticket_allocate(cmd->tickets, cmd->lens);
    if(status) {
        errprint(status, ws->cmd_output);
        lgl_clear_line(ws->cmd_input, ws->max_x);
        free(cmd->tickets);
        free(cmd->lens);
        free(cmd->input);
        return status;
    }

    split_input(cmd->tickets, cmd->input);

    free(cmd->input);
    free(cmd->lens);

    status = valid_args(cmd);
    if(status) {
        errprint(status, ws->cmd_output);
        lgl_clear_line(ws->cmd_input, ws->max_x);
        tickets_free(cmd->tickets);
        return status;
    }

    return status;
}

static void start_cmd(int y)
/*Outputs the command line character*/
{
    move(y, 0);
    addch(lgl_key_command);
    move(y, 1);
    echo();
    refresh();
}

int lgl_command_process(struct window_state *ws)
/*Fills a string with characters*/
{
    int status = 0;
    struct cmd_state cmd;
    
    lgl_clear_line(ws->cmd_output, ws->max_x);

    start_cmd(ws->cmd_input);
    
    status = parse_cmd(&cmd, ws);
    if(status == 0) {
        cmd_dispatcher(cmd.flag, cmd.arg, cmd. tickets, ws);
        tickets_free(cmd.tickets);
    }
    

    lgl_clear_line(ws->cmd_input, ws->max_x);
    noecho();
    curs_set(0);
    refresh();

    return status;
}

