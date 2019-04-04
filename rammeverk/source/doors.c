/**
 * @file
 * @brief Implementation file for the doors module.
 */
#include "doors.h"

void open_door() {
    elev_set_door_open_lamp(1);
}
void close_door() {
    elev_set_door_open_lamp(0);
}

void doors_change_state(int close) {
    if (close) {
        close_door();
    } else
    {
        open_door();
    }
}
