#include <stdio.h>

#include "devices.h"
#include "http.h"

void handle_keycode(const unsigned short key_code)
{
    switch (key_code) {
    case 57: // Space bar (toggle scene)
        send_message("{\"setScene\":null}");
        break;

    // Numpad 1-9 colors
    case 79:
        set_color(0);
        break;
    case 80:
        set_color(40);
        break;
    case 81:
        set_color(80);
        break;
    case 75:
        set_color(120);
        break;
    case 76:
        set_color(160);
        break;
    case 77:
        set_color(200);
        break;
    case 71:
        set_color(240);
        break;
    case 72:
        set_color(280);
        break;
    case 73:
        set_color(320);
        break;

    case 82: // Numbad 0 (warm)
        set_lighting("{\"colorTemp\":\"warm\",\"power\":true}");
        break;
    case 83: // Numpad . (cold)
        set_lighting("{\"colorTemp\":\"cold\",\"power\":true}");
        break;
    case 96: // Numpad enter (off)
        set_lighting("{\"power\":false}");
        break;
    case 74: // Numpad minus (brightness down)
        set_lighting("{\"adjustBrightness\":-20,\"power\":true}");
        break;
    case 78: // Numpad plus (brightness up)
        set_lighting("{\"adjustBrightness\":20,\"power\":true}");
        break;
    default:
        printf("Received unimplemented keycode [%u]\n", key_code);
    }
}
