#pragma once
#include <stdlib.h>

char **get_keyboard_paths(size_t *const keyboard_count);

int monitor_keyboards(const size_t keyboard_count, const char **keyboard_paths);
