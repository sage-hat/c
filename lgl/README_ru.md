---
name: Little Game Library
version: 0.1
author: Sage
date: 2026-06-04
edit_date: 2026-06-04
---
### Структура

1. **Название и краткое описание**
2. **Сборка**
3. **Использование**
4. **API**
5. **Пример**

---
# LGL - Little Game Library

Библиотека для создания консольных игр с использованием ncurses. Управление окном, границы, интерфейс, консоль команд.
## Сборка

```bash
cd src
gcc -c -I. parse.c cmd.c interface.c error.c get.c lgl.c
ar rcs ../lib/liblgl.a *.o
```

## Подключение к проекту

В своём проекте добавь:

```c
#include "lgl.h"
```

Компиляция:

```bash
gcc your_game.c -I/path/to/lgl/include -L/path/to/lgl/lib -llgl -lncurses -o game
```

## Публичные функции

### Инициализация и очистка

- `window_state_t *lgl_init()` — инициализирует curses, создаёт окно, возвращает указатель на состояние окна. При ошибке возвращает NULL.
- `void lgl_cleanup(window_state_t *ws)` — завершает curses и освобождает память.

### Управление окном

- `void lgl_execute_resize(window_state_t *ws)` — обрабатывает изменение размера окна (обычно вызывается при KEY_RESIZE).
- `void lgl_clear_line(int y, int x)` — очищает строку `y` до позиции `x`.

### Команды

- `int lgl_command_process(window_state_t *ws)` — обрабатывает ввод команд (вызывается при нажатии `/`). Возвращает 0 при успехе, иначе код ошибки.

### Геттеры (получение координат)

- `int lgl_get_std_output(window_state_t *ws)` — строка для обычного вывода.
- `int lgl_get_ui_top(window_state_t *ws)` — строка верхней UI-панели.
- `int lgl_get_ui_bottom(window_state_t *ws)` — строка нижней UI-панели.
- `int lgl_get_play_field_top(window_state_t *ws)` — верхняя граница игрового поля.
- `int lgl_get_play_field_bottom(window_state_t *ws)` — нижняя граница игрового поля.
- `int lgl_get_play_field_left(window_state_t *ws)` — левая граница игрового поля.
- `int lgl_get_play_field_right(window_state_t *ws)` — правая граница игрового поля.

## Пример использования

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
    
    // здесь твоя игровая логика...
    
    lgl_cleanup(ws);
    return 0;
}
```

## Зависимости

- ncurses (libncurses)

