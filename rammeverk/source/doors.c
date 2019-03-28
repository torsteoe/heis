#include "doors.h"

void doors_open_door() {
    elev_set_door_open_lamp(1);
}
void doors_close_door() {
    elev_set_door_open_lamp(0);
}