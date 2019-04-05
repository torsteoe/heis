/**
 * @file
 * @brief Implementation file for the doors module.
 */
#include "doors.h"

//hjelpefunksjoner
static void m_open_door();
static void m_close_door();


void m_open_door() {
    elev_set_door_open_lamp(1);
}
void m_close_door() {
    elev_set_door_open_lamp(0);
}

void doors_change_state(int close) {
    if (close) {
        m_close_door();
    } else
    {
        m_open_door();
    }
}
