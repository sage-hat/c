#include "cmd.h" 
#include <string.h>
#include <stdlib.h>

static void execute_echo(int output, char **tickets)
{
    mvprintw(output, 0, "%s", tickets[arg_1]);
}

static void execute_print(const struct window_state *ws, char **tickets)
{
    if(0 == strcmp(tickets[arg_1], "std")) {
        mvprintw(ws->std_output, 0, "%s", tickets[arg_2]);
    }
    if(0 == strcmp(tickets[arg_1], "uit")) {
        mvprintw(ws->ui_top, 0, "%s", tickets[arg_2]);
    }
    if(0 == strcmp(tickets[arg_1], "uib")) {
        mvprintw(ws->ui_bottom, 0, "%s", tickets[arg_2]);
    }
    refresh();
}

static void execute_clear(const struct window_state *ws, char **tickets)
{
    if(0 == strcmp(tickets[arg_1], "std")) {
        clear_line(ws->std_output, ws->max_x);
    }
    if(0 == strcmp(tickets[arg_1], "uit")) {
        clear_line(ws->ui_top, ws->max_x);
    }
    if(0 == strcmp(tickets[arg_1], "uib")) {
        clear_line(ws->ui_bottom, ws->max_x);
    }
    refresh();

}

static void execute_exit()
{
    endwin();
    exit(0);
}

static void execute_refresh(const struct window_state *ws)
{
    erase();
    set_border(ws);
}

void cmd_dispatcher(enum cmd_code flag, char **tickets, const struct window_state *ws)
/*The process of calling functions depending on the received command code*/
{
    switch(flag) {
        case cmd_echo:
            execute_echo(ws->cmd_output, tickets);
            break;
        case cmd_print:
            execute_print(ws, tickets);
            break;
        case cmd_clear:
            execute_clear(ws, tickets);
            break;
        case cmd_exit:
            execute_exit();
            break;
        case cmd_refresh:
            execute_refresh(ws);
            break;

    }
}
