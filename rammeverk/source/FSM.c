
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

    while (elev_get_floor_sensor_signal()==-1) {
        elev_set_motor_direction(DIRN_DOWN);
    }
    elev_set_motor_direction(DIRN_STOP);
    now_state = NOTMOVINGATFLOOR;
    
    queue_set_previous_floor(elev_get_floor_sensor_signal());  
} 



//setter state =  NOTMOVINGATFLOOR


void FSM_changeState(/*variables: previous_floor, current order, stop_button_pressed*/) {


    switch (now_state) {
       
        case NOTMOVINGATFLOOR:
            elev_set_motor_direction(DIRN_STOP);
            //call queue_arrived_at_floor(elev_current_floor)
            
            //if (queue_priority_order < elev_current_floor og ikke lik -1)
            //elev_set_motor_direction(DIRN_DOWN);
                now_state = MOVINGDOWN;

            //else if (queue_priority_order > elev_current_floor og ikke lik -1)
            //elev_set_motor_direction(DIRN_UP);
                now_state = MOVINGUP;

            //else if ordered to same floor
                now_state = NOTMOVINGATFLOOR;

            //else if stop_button_pressed
                now_state = STOPSTATE;

            break;
        case MOVINGDOWN:
            elev_set_motor_direction(DIRN_DOWN);
            //if (queue_should_i_stop_at_floor(elev_current_floor, direction=0))
            //elev_set_motor_direction(DIRN_STOP);
                now_state = NOTMOVINGATFLOOR;

            //else if stop_button_pressed
            //elev_set_motor_direction(DIRN_STOP);
                now_state = STOPSTATE;
            break;
        case MOVINGUP:
            elev_set_motor_direction(DIRN_UP);
            //if (queue_should_i_stop_at_floor(elev_current_floor, direction=1))
            //elev_set_motor_direction(DIRN_STOP);
                now_state = NOTMOVINGATFLOOR;

            //else if stop_button_pressed
            //elev_set_motor_direction(DIRN_STOP);
                now_state = STOPSTATE;
            break;
        case STOPSTATE:
            elev_set_motor_direction(DIRN_STOP);
            queue_reset_orders();    
            //if !stop_button_pressed && on_floor_now
                now_state = NOTMOVINGATFLOOR ;

            //else if !stop_button_pressed && on_floor_now
                now_state = NOTMOVINGMIDDLE;
            break;
        case NOTMOVINGMIDDLE:

            //if (queue_priority_order < elev_current_floor) &&!stop_button_pressed
            //elev_set_motor_direction(DIRN_DOWN);
            now_state = MOVINGDOWN;

            //else if (queue_priority_order > elev_current_floor) &&!stop_button_pressed
            //elev_set_motor_direction(DIRN_UP);
            now_state = MOVINGUP;
            break;

    }
}