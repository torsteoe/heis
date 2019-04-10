/**
 * @file
 * @brief Implementation file for the lights module.
 */
#include "lights.h"
#include "malloc.h"
//hjelpefunksjoner

static void m_set_floor_indicator_lights(int previous_floor);
static void m_set_order_indicator_lights(int ** pp_orders);


void lights_update_lights(int previous_floor, int ** pp_orders) {
    m_set_floor_indicator_lights(previous_floor);
    m_set_order_indicator_lights(pp_orders);
}

void m_set_floor_indicator_lights(int previous_floor) {
    elev_set_floor_indicator(previous_floor);
}


void m_set_order_indicator_lights(int ** pp_orders) {
    
    int * up = pp_orders[0];
    int * down = pp_orders[1];
    int * panel = pp_orders[2];

    for (int i = 0; i<3; i++) {
        elev_set_button_lamp(BUTTON_CALL_UP, i, up[i]);
    }
    for (int i = 1; i<4; i++) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, i, down[i]);
    }
    for (int i = 0; i<4; i++) {
        elev_set_button_lamp(BUTTON_COMMAND, i, panel[i]);
    }
    free(pp_orders);
    pp_orders = NULL;
}