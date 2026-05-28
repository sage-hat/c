#include <curses.h>
#include <stdlib.h>
#include "string.h"
#include "move.h"
#include "parse.h"

#define _(STR) (STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

#ifndef DEB
static const char message[] = "@";
enum {key_escape = 27};
enum {key_command = '/'};
#endif

#ifndef DEB
/*
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
*/
#endif

#ifndef DEB
int main()
{
    int status;

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
            status = command_process(max_y);
            break;
        }
    }
    endwin();
    return status;
}
#else
int main(int, char **argv)
{
    int status;
    status = DEB_command_process(argv);
    return status;
}
#endif

