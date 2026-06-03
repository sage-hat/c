#ifndef LGL_PRIV_H_SENTRY
#define LGL_PRIV_H_SENTRY

#include "error.h"
#include "get.h"
#include "interface.h"
#include "parse.h"
#include "cmd.h" 

#include "state.h"

enum {lgl_key_command = '/'};
enum {buffer_size = 128};

typedef struct window_state window_state_t;

window_state_t* lgl_init(void);
void lgl_cleanup(window_state_t *ws);


#endif
