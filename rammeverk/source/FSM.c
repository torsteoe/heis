
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


void FSM_changeState() {


    switch (now_state) {
       
        case NOTMOVINGATFLOOR:

            elev_set_motor_direction(DIRN_STOP);
            queue_arrived_at_floor(elev_get_floor_sensor_signal());
            
            if (elev_get_stop_signal()) {
                now_state = STOPSTATE;
            }


            else if ((queue_get_priority_order() < queue_get_previous_floor()) && queue_get_priority_order() != -1) {
                now_state = MOVINGDOWN;
            }
                

            else if ((queue_get_priority_order() > queue_get_previous_floor()) && queue_get_priority_order() != -1) {
                printf("verdier: priority %d, previous %d  ", queue_get_priority_order(), queue_get_previous_floor());
                now_state = MOVINGUP;
            }
            
            //Kan sløyfes denne her
            else if (queue_get_priority_order() == queue_get_previous_floor()) {
                now_state = NOTMOVINGATFLOOR;
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
                }
            }
            break;

        case STOPSTATE:
            elev_set_motor_direction(DIRN_STOP);
            queue_reset_orders();   


            if (!elev_get_stop_signal() && elev_get_floor_sensor_signal() != -1) {
                queue_print_orders();
                now_state = NOTMOVINGATFLOOR ;
            }

            else if (!elev_get_stop_signal() && !(elev_get_floor_sensor_signal() != -1) ){
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