#include "elev.h"
#include <stdio.h>
#include "FSM.h"
#include "lights.h"
#include "queue.h"

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_STOP);
    FSM_init();
    queue_init();
    while (1) {



         if (elev_get_floor_sensor_signal() != -1) {
                queue_set_previous_floor(elev_get_floor_sensor_signal());

            } 


        queue_update_orders();
        lights_update_lights();
        
        FSM_changeState();
            
        if (elev_get_stop_signal()) {
            queue_print_orders();
            queue_reset_orders();
            lights_update_lights();
            break;
        }

        /* if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_UP);

            while(1) {

                if (elev_get_floor_sensor_signal() == N_FLOORS-1) {
                    elev_set_motor_direction(DIRN_DOWN);

                } else if (elev_get_floor_sensor_signal() ==0)  {
                    elev_set_motor_direction(DIRN_UP);
                }
            
           }

        } */






        
    }

    return 0;
}
