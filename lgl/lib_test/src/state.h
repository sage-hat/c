#ifndef STATE_H_SENTRY
#define STATE_H_SENTRY

enum {max_coins = 15};

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
    int height;
    int width;
    int offset_y;
    int offset_x;
    int py;
    int px;
    int score;
    int level;
    int score_goal;
    int is_lvlup;
    int resize_pendind;
    int y_coins[max_coins];
    int x_coins[max_coins];
};

#endif

