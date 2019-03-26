
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
            //if ordered down
                now_state = MOVINGDOWN;
            //else if ordered up
                now_state = MOVINGUP;
            //else if ordered to same floor
                now_state = NOTMOVINGATFLOOR;
            //else if stop_button_pressed
                now_state = STOPSTATE;

            break;
        case MOVINGDOWN:
            //if arrived at order
                now_state = NOTMOVINGATFLOOR;
            //if stop_button_pressed
                now_state = STOPSTATE;
            break;
        case MOVINGUP:
            //if arrived at order
                now_state = NOTMOVINGATFLOOR;
            //if stop_button_pressed
                now_state = STOPSTATE;
            break;
        case STOPSTATE:
            //if !stop_button_pressed && on_floor_now
                now_state = NOTMOVINGATFLOOR ;
            //if !stop_button_pressed && on_floor_now
                now_state = NOTMOVINGMIDDLE;
            break;
        case NOTMOVINGMIDDLE:
            //if ordered_up &&!stop_button_pressed
            now_state = MOVINGUP;
            //if ordered_down &&!stop_button_pressed
            now_state = MOVINGDOWN;
            break;

    }
}