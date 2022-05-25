#include <stdio.h>

#include "http.h"

int set_lighting(char *lighting_json)
{
    char buf[100]; // TODO: Make dynamic
    snprintf(buf, sizeof(buf), "{\"deviceUpdateRequest\":{\"id\":\"lights\",\"requestedState\":%s}}", lighting_json);
    return send_message(buf);
}

int set_color(unsigned hue)
{
    char buf[25];
    snprintf(buf, sizeof(buf), "{\"hue\":%u,\"power\":true}", hue);
    return set_lighting(buf);
}
