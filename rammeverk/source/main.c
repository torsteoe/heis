/**
 * @file
 * @brief The main file of the application.
 */
#include "FSM.h"
#include "lights.h"
#include "queue.h"

int main() {
    
    if (!FSM_init()) {
        return 1;
    };
    

    while (1) {

        queue_update_orders();
        lights_update_lights(queue_get_previous_floor(), queue_get_orders()); //kan gi int **orders som input parameter her
        FSM_update_state();

    }

    return 0;
}
