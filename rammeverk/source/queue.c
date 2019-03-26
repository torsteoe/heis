#include "queue.h"


const int ORDER_SIZE = 4;

static int previous_floor = -1;
static int up_orders[ORDER_SIZE];
static int down_orders[ORDER_SIZE];
static int panel_orders[ORDER_SIZE];



void queue_set_previous_floor(int current_floor) {
    previous_floor = current_floor;
}

int queue_get_previous_floor() {
    return previous_floor;
}



void queue_update_orders() {
    add_down_orders();
    add_up_orders();
    add_panel_orders();
}



void add_up_orders() {
    for (int i = 0; i<ORDER_SIZE-1; i++) {
        if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
            up_orders[i] = 1;
        }    
    }
}
void add_down_orders() {
    for (int i = 1; i<ORDER_SIZE; i++) {
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
            down_orders[i]=1;
        }
    }
}

void add_panel_orders() {
    for (int i = 0; i<ORDER_SIZE; i++) {
        if (elev_get_button_signal(BUTTON_COMMAND, i)) {
            panel_orders[i] = 1;
        }
        
    }
}

void queue_print_orders() {
    printf("Here comes the sun: \n") ;

    printf("Uporders: \n");

    for (int i = 0; i<ORDER_SIZE-1; i++) {
        printf("%d: %d,\t", i, up_orders[i]); 
    }

}
