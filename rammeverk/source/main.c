#include "elev.h"
#include <stdio.h>
#include "FSM.h"
#include "lights.h"
#include "queue.h"
#include "timer.h"

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_STOP);

    timer_init();
    FSM_init();
    queue_init();

    while (1) {



        
        queue_set_previous_floor(elev_get_floor_sensor_signal());



        queue_update_orders();
        lights_update_lights();
        
        FSM_changeState();
            
        






        
    }

    return 0;
}
