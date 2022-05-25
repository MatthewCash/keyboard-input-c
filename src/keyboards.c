#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>

#include "keys.h"

#define INPUT_DEV_PATH "/dev/input/by-id/"

char **get_keyboard_paths(size_t *const keyboard_count)
{
    DIR *keyboard_dir = opendir(INPUT_DEV_PATH);

    char **keyboard_paths = NULL;
    *keyboard_count = 0;

    struct dirent *dir_entry;

    while ((dir_entry = readdir(keyboard_dir)))
    {
        size_t d_name_len = strlen(dir_entry->d_name);

        if (d_name_len < 4)
            continue;
        if (strcmp(dir_entry->d_name + d_name_len - 3, "kbd") != 0)
            continue;

        keyboard_paths = (char**) realloc(keyboard_paths, sizeof(char *) * (*keyboard_count + 2));

        size_t keyboard_path_len = sizeof(INPUT_DEV_PATH) + d_name_len + 1;
        keyboard_paths[*keyboard_count] = (char*) malloc(sizeof(char) * keyboard_path_len);

        strncpy(keyboard_paths[*keyboard_count], INPUT_DEV_PATH, sizeof(INPUT_DEV_PATH));
        strncat(keyboard_paths[*keyboard_count], dir_entry->d_name, d_name_len);

        (*keyboard_count)++;
    }

    closedir(keyboard_dir);

    return keyboard_paths;
}

int monitor_keyboards(const size_t keyboard_count, const char **keyboard_paths)
{
    struct pollfd *poll_fds = malloc(sizeof(struct pollfd) * keyboard_count);

    for (size_t i = 0; i < keyboard_count; i++) {
        const int keyboard_fd = open(keyboard_paths[i], O_RDONLY);
        if (keyboard_fd < 1) {
            free(poll_fds);
            perror("An error occurred opening keyboard device");
            return 1;
        }

        poll_fds[i] = (struct pollfd) { .fd = keyboard_fd, .events = POLLIN };
    }

    struct input_event event;

    while (1) {
        const int poll_result = poll(poll_fds, 1, -1);
        if (poll_result < 0) {
            perror("An error occurred polling keyboard device");      
        }

        for (size_t i = 0; i < keyboard_count; i++) {
            // Skip if no new data
            if (!(poll_fds[i].revents & POLLIN)) continue;

            const ssize_t read_result = read(poll_fds[i].fd, &event, sizeof(event));
            if (read_result < 0)
            {
                perror("An error occurred reading keyboard device");
                continue;
            }

            // Skip if not a keypress/release
            if (!(event.type & EV_KEY)) continue;
            if (event.value != 1) continue;    

            handle_keycode(event.code);
        }
    }

    free(poll_fds);
    return 0;
}
