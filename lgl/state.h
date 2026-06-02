#ifndef STATE_H_SENTRY
#define STATE_H_SENTRY

struct window_state {
    /*Screen size*/
    int max_y;
    int max_x;

    /*Border*/
    int top_border;
    int bottom_border;
    int right_border_x;
    int left_border_x;

    /*Playing field*/
    int top_max_y;
    int bottom_max_y;
    int right_max_x;
    int left_max_x;

    /*User interface*/
    int ui_top;
    int ui_bottom;
    int std_output;

    /*Command interface*/
    int cmd_input;
    int cmd_output;
};

struct game_state {
    int max_y;
    int max_x;
    int min_y;
    int min_x;
    int py;
    int px;
};

#endif
