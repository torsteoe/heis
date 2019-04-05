/**
 * @file
 * @brief Implementation file for the lights module.
 */
#include "lights.h"

//hjelpefunksjoner

static void m_set_floor_indicator_lights();
static void m_set_order_indicator_lights();


void lights_update_lights() {
    m_set_floor_indicator_lights();
    m_set_order_indicator_lights();
}

void m_set_floor_indicator_lights() {
    elev_set_floor_indicator(queue_get_previous_floor());
}


void m_set_order_indicator_lights() {
    int * up = queue_get_up_orders();
    int * down = queue_get_down_orders();
    int * panel = queue_get_panel_orders();

    for (int i = 0; i<3; i++) {
        elev_set_button_lamp(BUTTON_CALL_UP, i, up[i]);
    }
    for (int i = 1; i<4; i++) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, i, down[i]);
    }
    for (int i = 0; i<4; i++) {
        elev_set_button_lamp(BUTTON_COMMAND, i, panel[i]);
    }
}