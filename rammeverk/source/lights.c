#include "lights.h"


void lights_update_lights() {
    set_floor_indicator_lights();
}

void set_floor_indicator_lights() {
    elev_set_floor_indicator(queue_get_previous_floor());
}
