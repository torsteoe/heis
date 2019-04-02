#include "doors.h"

void open_door() {
    elev_set_door_open_lamp(1);
}
void close_door() {
    elev_set_door_open_lamp(0);
}

void doors_change_state(int timeout) {
    if (timeout) {
        close_door();
    } else
    {
        open_door();
    }
}
