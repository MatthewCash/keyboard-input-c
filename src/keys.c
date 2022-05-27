#include <stdio.h>

#include "devices.h"
#include "http.h"
#include <linux/input-event-codes.h>

void handle_keycode(const unsigned short key_code)
{
    switch (key_code) {
    case KEY_SPACE: // toggle scene
        send_message("{\"setScene\":null}");
        break;
    case KEY_LEFT:
    case KEY_DOWN:
        // scene off
        send_message("{\"setScene\":\"off\"}");
        break;
    case KEY_RIGHT:
    case KEY_UP:
        // scene on
        send_message("{\"setScene\":\"on\"}");
        break;

    // Numpad 1-9 colors
    case KEY_KP1:
        set_color(0);
        break;
    case KEY_KP2:
        set_color(40);
        break;
    case KEY_KP3:
        set_color(80);
        break;
    case KEY_KP4:
        set_color(120);
        break;
    case KEY_KP5:
        set_color(160);
        break;
    case KEY_KP6:
        set_color(200);
        break;
    case KEY_KP7:
        set_color(240);
        break;
    case KEY_KP8:
        set_color(280);
        break;
    case KEY_KP9:
        set_color(320);
        break;

    case KEY_KP0: // warm
        set_lighting("{\"colorTemp\":\"warm\",\"power\":true}");
        break;
    case KEY_KPDOT: // cold
        set_lighting("{\"colorTemp\":\"cold\",\"power\":true}");
        break;
    case KEY_KPENTER: // off
        set_lighting("{\"power\":false}");
        break;
    case KEY_KPMINUS: // brightness down
        set_lighting("{\"adjustBrightness\":-20,\"power\":true}");
        break;
    case KEY_KPPLUS: // brightness up
        set_lighting("{\"adjustBrightness\":20,\"power\":true}");
        break;
    default:
        printf("Received unimplemented keycode [%u]\n", key_code);
    }
}
