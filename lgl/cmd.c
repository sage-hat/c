/*
* Module:     cmd.c
* Author:     sage
* Created:    01.06.2026
* Modified:   02.06.2026
* Version:    0.1
* Description: Controls the execution of commands
* 
* Comments: 
*/
#include "cmd.h" 

const char *commands[] = {
/*List of valid commands*/
    "echo",
    "print",
    "clear",
    "exit",
    "refresh"
};

const char *arguments[] = {
/*List of valid arguments*/
    "std",
    "uit",
    "uib"
};

static void execute_echo(int output, char **tickets)
/*Execute command echo*/
{
    mvprintw(output, 0, "%s", tickets[arg_1]);
}

static void execute_print(const struct window_state *ws, int arg, char **tickets)
/*Execute command print*/
{
    switch(arg) {
        case arg_std:
            mvprintw(ws->std_output, 0, "%s", tickets[arg_2]);
            break;
        case arg_uit:
            mvprintw(ws->ui_top, 0, "%s", tickets[arg_2]);
            break;
        case arg_uib:
            mvprintw(ws->ui_bottom, 0, "%s", tickets[arg_2]);
            break;
    }
    refresh();
}

static void execute_clear(const struct window_state *ws, int arg)
/*Execute command clear*/
{
    switch(arg) {
        case arg_std:
            clear_line(ws->std_output, ws->max_x);
            break;
        case arg_uit:
            clear_line(ws->ui_top, ws->max_x);
            break;
        case arg_uib:
            clear_line(ws->ui_bottom, ws->max_x);
            break;
    }
    refresh();
}

static void execute_exit()
/*Execute command exit*/
{
    endwin();
    exit(0);
}

static void execute_refresh(struct window_state *ws)
/*Execute command refresh*/
{
    erase();
    execute_resize(ws);
}

void cmd_dispatcher(enum cmd_code flag, enum cmd_args_name arg, char **tickets, struct window_state *ws)
/*The process of calling functions depending on the received command code*/
{
    switch(flag) {
        case cmd_echo:
            execute_echo(ws->cmd_output, tickets);
            break;
        case cmd_print:
            execute_print(ws, arg, tickets);
            break;
        case cmd_clear:
            execute_clear(ws, arg);
            break;
        case cmd_exit:
            execute_exit();
            break;
        case cmd_refresh:
            execute_refresh(ws);
            break;
    }
}
