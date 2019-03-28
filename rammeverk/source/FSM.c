
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

void FSM_init() { //kjører ned fram til vi enten:
//er på etasje (kjører så lenge FLOOR!=-1)
    elev_set_motor_direction(DIRN_DOWN);
    while (elev_get_floor_sensor_signal()==-1);
    elev_set_motor_direction(DIRN_STOP);
    now_state = NOTMOVINGATFLOOR;
    
    queue_set_previous_floor(elev_get_floor_sensor_signal());  
} 



//setter state =  NOTMOVINGATFLOOR
int timeout;

void FSM_changeState() {


    switch (now_state) {
       
        case NOTMOVINGATFLOOR:
            timeout = timer_is_timeout();
            if (timeout) {
                doors_close_door();
            } else
            {
                doors_open_door();
            }
            
            elev_set_motor_direction(DIRN_STOP);
            queue_arrived_at_floor(queue_get_previous_floor());
            
            if (elev_get_stop_signal()) {
                now_state = STOPSTATE;
            }


            else if ((queue_get_priority_order() < queue_get_previous_floor()) && queue_get_priority_order() != -1) {
                if (timeout) {
                    now_state = MOVINGDOWN;
                }
            }
                

            else if ((queue_get_priority_order() > queue_get_previous_floor()) && queue_get_priority_order() != -1) {
                if (timeout) {
                    now_state = MOVINGUP;
                }
            }
            
            //burde gjøres finere, holder å sjekke om den er i priority_order() i det heletatt.
            else if (queue_should_I_stop_at_floor(queue_get_previous_floor(),0) || queue_should_I_stop_at_floor(queue_get_previous_floor(),0) ) {
                now_state = NOTMOVINGATFLOOR; //can be removed but is kept for legibility.
                timer_reset();
            }

            break;

        case MOVINGDOWN:
            elev_set_motor_direction(DIRN_DOWN);

            if (elev_get_stop_signal()) {
                now_state = STOPSTATE;
            }

            else if (elev_get_floor_sensor_signal() != -1) {
                if (queue_should_I_stop_at_floor(elev_get_floor_sensor_signal(), 0)) {
                    now_state = NOTMOVINGATFLOOR;
                    timer_reset();
                }
            }

            
            break;

        case MOVINGUP:
            elev_set_motor_direction(DIRN_UP);
            
            if (elev_get_stop_signal()) {
                now_state = STOPSTATE;
            }

            else if (elev_get_floor_sensor_signal() != -1) {
                if (queue_should_I_stop_at_floor(elev_get_floor_sensor_signal(), 1)) {
                    now_state = NOTMOVINGATFLOOR;
                    timer_reset();
                }
            }
            break;

        case STOPSTATE:
            elev_set_motor_direction(DIRN_STOP);
            elev_set_stop_lamp(1);
            timer_reset();
            queue_reset_orders();   
            if (elev_get_floor_sensor_signal() != -1) {
                doors_open_door();
            }

            if (!elev_get_stop_signal() && elev_get_floor_sensor_signal() != -1) {
                elev_set_stop_lamp(0);
                queue_print_orders();
                now_state = NOTMOVINGATFLOOR ;
            }

            else if (!elev_get_stop_signal() && !(elev_get_floor_sensor_signal() != -1) ){
                elev_set_stop_lamp(0);
                queue_print_orders();
                now_state = NOTMOVINGMIDDLE;
            }

            break;

        case NOTMOVINGMIDDLE:
            
            if (!elev_get_stop_signal()) {
                if ((queue_get_priority_order() < queue_get_previous_floor()) && queue_get_priority_order() != -1) {
                    now_state = MOVINGDOWN;
                }  
                else if ((queue_get_priority_order() > queue_get_previous_floor()) && queue_get_priority_order() != -1) {
                    now_state = MOVINGUP;
                }
            }
            break;

    }
}