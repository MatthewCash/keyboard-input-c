#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <poll.h>
#include <string.h>

#include "keyboards.h"

int main()
{
    size_t keyboard_count = 0;
    char **keyboard_paths = get_keyboard_paths(&keyboard_count);

    if (keyboard_count == 0 || keyboard_paths == NULL)
    {
        fprintf(stderr, "No keyboards found!\n");
        return 1;
    }

    for (size_t i = 0; i < keyboard_count; i++) {
        printf("Loaded keyboard at [%s]\n", keyboard_paths[i]);
    }

    monitor_keyboards(keyboard_count, (const char**) keyboard_paths);

    for (size_t i = 0; i < keyboard_count; i++) {
        free(keyboard_paths[i]);
    }

    free(keyboard_paths);
    return 0;
}
