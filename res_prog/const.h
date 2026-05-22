#ifndef CONST_H_SENTRY
#define CONST_H_SENTRY

#include <locale.h>
#include <libintl.h>

#define _(STR) gettext(STR)    /*Macro for translatable strings*/
#define N_(STR) (STR)   /*Macro for non-translatable strings*/

/*--== Constant array block ==--*/
extern const char *colors[];

extern const char *valid_flags[];

/* --== Constant block ==--*/

enum colors_code{
    black, brown, red,
    orange, yellow, green,
    blue, violet, grey,
    white, silver, gold
};

enum flag_codes{
    help,
    decode,
    encode
};

enum error_codes{
    ERR_ARRG_COUNT = 1,  
    ERR_INVALID_FLAG,
    ERR_MEMORY,
    ERR_COLOR,
    ERR_FARG_1,
    ERR_NOMINAL_SILVER,
    ERR_NOMINAL_GOLD,
    ERR_TOL_1,
    ERR_TOL_2,
    ERR_TOL_3,
    ERR_TOL_4
};

enum {nominal_1digt, nominal_2digit, multipler_code, tolerance_code};

enum {flags_number = 3};
enum {band_count = 4};
enum {colors_number = 12};
enum {args_number_decode = 6};
enum {args_number_help = 2};
enum {first_arg = 1};
enum {first_color_arg = 2};
enum {last_color_arg =6};
#endif
