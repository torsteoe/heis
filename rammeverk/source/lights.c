/**
 * @file
 * @brief Implementation file for the lights module.
 */
#include "lights.h"
#include "malloc.h"
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
    int ** all_orders = queue_get_orders();
    int * up = all_orders[0];
    int * down = all_orders[1];
    int * panel = all_orders[2];

    for (int i = 0; i<3; i++) {
        elev_set_button_lamp(BUTTON_CALL_UP, i, up[i]);
    }
    for (int i = 1; i<4; i++) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, i, down[i]);
    }
    for (int i = 0; i<4; i++) {
        elev_set_button_lamp(BUTTON_COMMAND, i, panel[i]);
    }
    free(all_orders);
    all_orders = NULL;
}