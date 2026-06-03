#ifndef LGL_PRIV_H_SENTRY
#define LGL_PRIV_H_SENTRY

typedef struct window_state window_state_t;

window_state_t* lgl_init(void);
void lgl_cleanup(window_state_t *ws);


enum errors {
    ERR_MEMORY = 1,
    ERR_BUFFER_OVERFLOW,
    ERR_UNKNOWN_COMMAND,
    ERR_UNKNOWN_ARG,
    ERR_WRONG_ARGS_COUNT
};

enum {lgl_key_command = '/'};

int lgl_command_process(struct window_state *ws);
void lgl_init_window(struct window_state *ws);
void lgl_execute_resize(struct window_state *ws);
void lgl_clear_line(int y, int x);


int lgl_get_std_output(struct window_state *ws);
int lgl_get_ui_top(struct window_state *ws);
int lgl_get_ui_bottom(struct window_state *ws);
int lgl_get_play_field_top(struct window_state *ws);
int lgl_get_play_field_bottom(struct window_state *ws);
int lgl_get_play_field_left(struct window_state *ws);
int lgl_get_play_field_right(struct window_state *ws);

#endif
