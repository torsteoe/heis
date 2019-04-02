
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
static int previous_direction; //0 for down, 1 for up

void FSM_init() { //kjører ned fram til vi enten:
//er på etasje (kjører så lenge FLOOR!=-1)
    elev_set_motor_direction(DIRN_DOWN);
    while (elev_get_floor_sensor_signal()==-1);
    elev_set_motor_direction(DIRN_STOP);
    now_state = NOTMOVINGATFLOOR;
    previous_direction = 0;
    queue_set_previous_floor(elev_get_floor_sensor_signal());  
} 


//setter state =  NOTMOVINGATFLOOR
int timeout;
int FSM_get_state() {
    return now_state;
}


void FSM_changeState() {


    switch (now_state) {
       
        case NOTMOVINGATFLOOR:
            timeout = timer_is_timeout();
            
            doors_change_state(timeout);
            
            elev_set_motor_direction(DIRN_STOP);
            
            
            if (elev_get_stop_signal()) {
                now_state = STOPSTATE;
                break;
            }

            //checks if order on this floor exists in any order_queue
            else if (queue_should_I_stop_at_floor(queue_get_previous_floor(),2)) {
                now_state = NOTMOVINGATFLOOR; //can be removed but is kept for legibility.
                timer_reset();
                queue_arrived_at_floor(queue_get_previous_floor());
                break;
            }
            queue_arrived_at_floor(queue_get_previous_floor());



            if ((queue_get_priority_order() < queue_get_previous_floor()) && orders_exist()) {
                if (timeout) {
                    now_state = MOVINGDOWN;
                }
            }
                

            else if ((queue_get_priority_order() > queue_get_previous_floor()) && orders_exist()) {
                if (timeout) {
                    now_state = MOVINGUP;
                }
            }
            
             
            break;

        case MOVINGDOWN:
            elev_set_motor_direction(DIRN_DOWN);
            assert(orders_exist());
            if (elev_get_stop_signal()) {
                previous_direction = 0;
                now_state = STOPSTATE;
            }

            else if (on_floor()) {
                if (queue_should_I_stop_at_floor(elev_get_floor_sensor_signal(), 0)) {
                    now_state = NOTMOVINGATFLOOR;
                    timer_reset();
                }
                else if (!queue_orders_in_direction(0)) {
                    now_state = NOTMOVINGATFLOOR;
                }
            }

            
            break;

        case MOVINGUP:
            elev_set_motor_direction(DIRN_UP);
            assert(orders_exist());

            if (elev_get_stop_signal()) {
                previous_direction = 1;
                now_state = STOPSTATE;
            }

            else if (on_floor()) {
                if (queue_should_I_stop_at_floor(elev_get_floor_sensor_signal(), 1)) {
                    now_state = NOTMOVINGATFLOOR;
                    timer_reset();
                }
                else if (!queue_orders_in_direction(1)) {
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
         
            if (!elev_get_stop_signal()) {
                if ((queue_get_priority_order() < queue_get_previous_floor()) && orders_exist()) {
                    now_state = MOVINGDOWN;
                }  
                else if ((queue_get_priority_order() > queue_get_previous_floor()) && orders_exist()) {
                    now_state = MOVINGUP;
                }
                else if ((queue_get_priority_order() == queue_get_previous_floor()) && orders_exist()) {
                    if (previous_direction == 0) {
                        now_state = MOVINGUP;
                    } else {
                        now_state = MOVINGDOWN;
                    }
                }
            }
            else if (elev_get_stop_signal()) {
                now_state = STOPSTATE;
            }


            break;

    }
}



int on_floor() {
    return (elev_get_floor_sensor_signal() != -1);
}
int orders_exist() {
    return (queue_get_priority_order() != -1);
}