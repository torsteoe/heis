/**
 * @file
 * @brief The main file of the application.
 */
#include "FSM.h"
#include "lights.h"
#include "queue.h"
/**
  Main operation loop, loops as long as elevator is operational.
  @return @c 1 if initiation fails, @c 0 if while-loop breaks.
*/
int main() {
    
    if (!FSM_init()) {
        return 1;
    };
    

    while (1) {

        queue_update_orders();
        
        FSM_update_state();
        lights_update_lights(queue_get_previous_floor(), queue_get_orders()); 
    }

    return 0;
}
