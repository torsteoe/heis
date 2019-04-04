/**
 * @file
 * @brief Implementation file for the state machine module.
 */
#include "FSM.h"


typedef enum STATES {
    //INIT, //maybe superfluous
    NOTMOVINGATFLOOR, 
    MOVINGDOWN,
    MOVINGUP,
    STOPSTATE,
    NOTMOVINGMIDDLE //mellom etasjer
} state;

static state now_state = NOTMOVINGMIDDLE;
static elev_motor_direction_t previous_direction; //-1 for down, 1 for up

void FSM_init() { //kjører ned fram til vi enten:
//er på etasje (kjører så lenge FLOOR!=-1)
    elev_set_motor_direction(DIRN_UP);
    while (elev_get_floor_sensor_signal()==-1);
    elev_set_motor_direction(DIRN_STOP);
    now_state = NOTMOVINGATFLOOR;
    previous_direction = DIRN_DOWN;
    queue_set_previous_floor(elev_get_floor_sensor_signal());  


    timer_init();
    queue_init();
} 


int timeout;
int FSM_get_state() {
    return now_state;
}


void FSM_changeState() {


    switch (now_state) {
       
        case NOTMOVINGATFLOOR:
            timeout = timer_is_timeout(); //in case timer changes during function.
            elev_set_motor_direction(DIRN_STOP);
            doors_change_state(timeout);
            
            
            if (elev_get_stop_signal()) {
                now_state = STOPSTATE;
                break;
            }

            //checks if order on this floor exists in any order_queue
            else if (ordered_to_same_floor()) {
                now_state = NOTMOVINGATFLOOR; //can be removed but is kept for legibility.
                timer_reset();
                queue_delete_floor_orders();
                break;
            }
            
            queue_delete_floor_orders();

            if (timeout) {
                if (ordered_down()) {
                    now_state = MOVINGDOWN;
                }
                
                else if (ordered_up()) {
                    now_state = MOVINGUP;
                }
            }
  
            break;

        case MOVINGDOWN:
            elev_set_motor_direction(DIRN_DOWN);

            if (elev_get_stop_signal()) { 
                previous_direction = DIRN_DOWN; //In case we are stopped in between floors.
                now_state = STOPSTATE;
            }

            else if (on_floor()) {
                if (queue_should_I_stop_at_floor(DIRN_DOWN)) {
                    now_state = NOTMOVINGATFLOOR;
                    timer_reset();
                }
                else if (!queue_orders_in_direction(DIRN_DOWN)) { //safety measure
                    now_state = NOTMOVINGATFLOOR;
                }
            }

            
            break;

        case MOVINGUP:
            elev_set_motor_direction(DIRN_UP);

            if (elev_get_stop_signal()) {
                previous_direction = DIRN_UP;
                now_state = STOPSTATE;
            }

            else if (on_floor()) {
                if (queue_should_I_stop_at_floor(DIRN_UP)) {
                    now_state = NOTMOVINGATFLOOR;
                    timer_reset();
                }
                else if (!queue_orders_in_direction(DIRN_UP)) {
                    now_state = NOTMOVINGATFLOOR;
                }
            }
            break;

        case STOPSTATE:
            elev_set_motor_direction(DIRN_STOP);
            elev_set_stop_lamp(1);
            timer_reset();
            queue_reset_orders();   
            

            doors_change_state(!(on_floor()));
            

            if (!elev_get_stop_signal() && on_floor()) {
                elev_set_stop_lamp(0);
                now_state = NOTMOVINGATFLOOR ;
            }

            else if (!elev_get_stop_signal() && !(on_floor()) ){
                elev_set_stop_lamp(0);
                now_state = NOTMOVINGMIDDLE;
            }

            break;

        case NOTMOVINGMIDDLE:

            if (elev_get_stop_signal()) {
                now_state = STOPSTATE;
            }
            else {
                if (ordered_down()) {
                    now_state = MOVINGDOWN;
                }  
                else if (ordered_up()) {
                    now_state = MOVINGUP;
                }

                else if (ordered_to_same_floor()) {
                    if (previous_direction == DIRN_DOWN) {
                        now_state = MOVINGUP;
                    } else {
                        now_state = MOVINGDOWN;
                    }
                }
            }
            
            break;

    }
}
int ordered_to_same_floor() {
    return (queue_should_I_stop_at_floor(2));
}
int ordered_up() {
    return (orders_exist() && queue_get_priority_order() > queue_get_previous_floor());
}
int ordered_down() {
    return (orders_exist() && queue_get_priority_order() < queue_get_previous_floor());
}
int on_floor() {
    return (elev_get_floor_sensor_signal() != -1);
}
int orders_exist() {
    return (queue_get_priority_order() != -1);
}