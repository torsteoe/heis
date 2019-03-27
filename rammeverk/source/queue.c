#include "queue.h"


const int ORDER_SIZE = 4;

static int previous_floor = -1;
static int up_orders[ORDER_SIZE]; 
static int down_orders[ORDER_SIZE]; 
static int panel_orders[ORDER_SIZE];
static int priority_orders[ORDER_SIZE]; //default -1 




void queue_set_previous_floor(int current_floor) {
    previous_floor = current_floor;
}

int queue_get_previous_floor() {
    return previous_floor;
}

int * queue_get_up_orders() {
    return up_orders;
}
int * queue_get_down_orders() {
    return down_orders;
}

int * queue_get_panel_orders() {
    return panel_orders;
}
int queue_get_priority_order() {
    return priority_orders[0];
}

//Returns 1 if one must stop, returns 0 otherwise;
//direction: 0 is down, 1 is up : replace this with DIRN_DOWN and DIRN_UP if possible?
int queue_should_I_stop_at_floor(int floor, int direction) {
    if (direction==0) {
        return (down_orders[floor] || panel_orders[floor]); //test if this works.
    }
    else { //direction is up
        return (up_orders[floor] || panel_orders[floor]);
    }
}


//erases all orders for given floor
void queue_arrived_at_floor(int floor) {
    
        
    up_orders[floor] = 0;
    down_orders[floor] = 0;
    panel_orders[floor] = 0;
    
    //iterates priority_orders:
        //if floor in priority_orders all other floors are moved one spot up in priority.
    for (int i = 0; i<ORDER_SIZE; i++) {
        if (priority_orders[i] == floor) {
            for (int idx = i; idx<ORDER_SIZE-1; idx++) {
                priority_orders[idx] = priority_orders[idx+1];
            }
            priority_orders[ORDER_SIZE-1] = -1;
            break;
        
        }
    }
    
}





void queue_init() {
    queue_reset_orders();
}


void queue_update_orders() {
    add_down_orders();
    add_up_orders();
    add_panel_orders();
    //priority_orders updated in the three functions above
}



void add_up_orders() {
    for (int i = 0; i<ORDER_SIZE-1; i++) {
        if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
            up_orders[i] = 1;
            add_priority_orders(i);
        }    
    }
}
void add_down_orders() {
    for (int i = 1; i<ORDER_SIZE; i++) {
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
            down_orders[i]=1;
            add_priority_orders(i);
        }
    }
}

void add_panel_orders() {
    for (int i = 0; i<ORDER_SIZE; i++) {
        if (elev_get_button_signal(BUTTON_COMMAND, i)) {
            panel_orders[i] = 1;
            add_priority_orders(i);
        }
        
    }
}

//receives a floor, checks if in list, adds if not.
void add_priority_orders(int floor) {

    //go through priority_orders
    //break if floor in list
    //add if -1, then break
    for (int i = 0; i<ORDER_SIZE;i++) {
        if (priority_orders[i] == floor) {
            break;
        }
        if (priority_orders[i] == -1) {
            priority_orders[i] = floor;
            break;
        }
    }
}



void queue_reset_orders() {
    for (int i = 0; i<ORDER_SIZE; i++) {
            up_orders[i] = 0;
            down_orders[i] = 0;
            panel_orders[i] = 0;
            priority_orders[i] = -1;
    }
}



void queue_print_orders() {

    printf("Here comes the sun: \n") ;

    printf("Uporders: \n");
    for (int i = 0; i<ORDER_SIZE-1; i++) {
        printf("%d: %d,\t", i, up_orders[i]); 
    }
    printf("\n");

    printf("down_orders: \n");
    for (int i = 1; i<ORDER_SIZE; i++) {
        printf("%d: %d,\t", i, down_orders[i]); 
    }
    printf("\n");

    printf("panel_orders: \n");
    for (int i = 0; i<ORDER_SIZE; i++) {
        printf("%d: %d,\t", i, panel_orders[i]); 
    }
    printf("\n");

    printf("priority_orders: \n");
    for (int i = 0; i<ORDER_SIZE; i++) {
        printf("%d: %d,\t", i, priority_orders[i]); 
    }
    printf("\n");

}