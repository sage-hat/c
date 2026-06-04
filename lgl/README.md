---
name: Little Game Library
version: 0.1
author: Sage
date: 2026-06-04
edit_date: 2026-06-04
---
### Structure

1. **Name and brief description**
2. **Building**
3. **Usage**
4. **API**
5. **Example**

---
# LGL - Little Game Library

A library for creating console games using ncurses. Window management, borders, interface, command console.

## Building

```bash
cd src
gcc -c -I. parse.c cmd.c interface.c error.c get.c lgl.c
ar rcs ../lib/liblgl.a *.o
```

## Linking with Your Project

In your project, add:

```c
#include "lgl.h"
```

Compilation:

```bash
gcc your_game.c -I/path/to/lgl/include -L/path/to/lgl/lib -llgl -lncurses -o game
```

## Public Functions

### Initialization and Cleanup

- `window_state_t *lgl_init()` — initializes curses, creates a window, returns a pointer to the window state. Returns NULL on error.
- `void lgl_cleanup(window_state_t *ws)` — shuts down curses and frees allocated memory.

### Window Management

- `void lgl_execute_resize(window_state_t *ws)` — handles window resize (typically called on KEY_RESIZE).
- `void lgl_clear_line(int y, int x)` — clears line `y` up to position `x`.

### Commands

- `int lgl_command_process(window_state_t *ws)` — processes command input (called when `/` is pressed). Returns 0 on success, otherwise an error code.

### Getters (Coordinate Access)

- `int lgl_get_std_output(window_state_t *ws)` — returns the line for standard output.
- `int lgl_get_ui_top(window_state_t *ws)` — returns the line for the top UI panel.
- `int lgl_get_ui_bottom(window_state_t *ws)` — returns the line for the bottom UI panel.
- `int lgl_get_play_field_top(window_state_t *ws)` — returns the top border of the playfield.
- `int lgl_get_play_field_bottom(window_state_t *ws)` — returns the bottom border of the playfield.
- `int lgl_get_play_field_left(window_state_t *ws)` — returns the left border of the playfield.
- `int lgl_get_play_field_right(window_state_t *ws)` — returns the right border of the playfield.

## Example Usage

```c
#include <stdio.h>
#include <time.h>
#include "lgl.h"

int main() {
    window_state_t *ws = lgl_init();
    if (ws == NULL) return 1;
    
    int top = lgl_get_play_field_top(ws);
    int bottom = lgl_get_play_field_bottom(ws);
    int left = lgl_get_play_field_left(ws);
    int right = lgl_get_play_field_right(ws);
    
    // Your game logic here...
    
    lgl_cleanup(ws);
    return 0;
}
```

## Dependencies

- ncurses (libncurses)