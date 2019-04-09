/**
 * @file
 * @brief Implementation file for the queue module.
 */
#include "queue.h"
#include "malloc.h"

const int ORDER_SIZE = 4;

static int previous_floor = -1;
static int up_orders[ORDER_SIZE]; 
static int down_orders[ORDER_SIZE]; 
static int panel_orders[ORDER_SIZE];
static int priority_orders[ORDER_SIZE]; //default -1 


//hjelpefunksjoner
static void m_add_up_orders();
static void m_add_down_orders();
static void m_add_panel_orders();
static void m_add_priority_orders(int floor);




int ** queue_get_orders() {
    int ** pp_orders = (int **) malloc(3*sizeof(up_orders));
    pp_orders[0] = up_orders;
    pp_orders[1] = down_orders;
    pp_orders[2] = panel_orders;
    return pp_orders;
}



int queue_get_previous_floor() {
    return previous_floor;
}

/* int * queue_get_up_orders() {
    return up_orders;
}
int * queue_get_down_orders() {
    return down_orders;
}

int * queue_get_panel_orders() {
    return panel_orders;
} */
int queue_get_priority_order() {
    return priority_orders[0];
}

//Returns 1 if one must stop, returns 0 otherwise;
//direction: -1 is down, 1 is up.
int queue_should_I_stop_at_floor(int direction) {
    int floor = elev_get_floor_sensor_signal();

    if (floor == -1) {
        return 0;
    }

    if (priority_orders[0] == floor) {
        return 1;
    }
    if (direction==-1) { //direction is down
        return (down_orders[floor] || panel_orders[floor]); 
    }
    else  { //direction is up
        return (up_orders[floor] || panel_orders[floor]);
    }
    
    
}


//erases all orders for given floor
void queue_delete_floor_orders() {
    int floor = previous_floor;
    assert(floor<4 && floor >= 0);
        
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

//Returns 1 if orders in this direction. 0 if no orders in direction. -1 is down, 1 is up
int queue_orders_in_direction(int direction) {
    int orders_exist = 0;

    for (int priority_idx = 0; priority_idx<ORDER_SIZE; priority_idx++) {
        if (direction == DIRN_DOWN) {
            for (int floor = 0; floor<previous_floor; floor++) {
                orders_exist += (priority_orders[priority_idx]==floor);
            }
        } else {
            for (int floor = previous_floor+1; floor<ORDER_SIZE; floor++) {
                orders_exist += (priority_orders[priority_idx]==floor);
            } 
        }
    }
    
    if (orders_exist==0) {
        printf("safety measure will be taken");
    }
    return (orders_exist>0);
}







void queue_update_orders() {

    int current_floor = elev_get_floor_sensor_signal();
    if (current_floor != -1){
        previous_floor = current_floor;
    }
    
    m_add_down_orders();
    m_add_up_orders();
    m_add_panel_orders();
    //priority_orders updated in the three functions above
}



void m_add_up_orders() {
    for (int i = 0; i<ORDER_SIZE-1; i++) {
        if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
            up_orders[i] = 1;
            m_add_priority_orders(i);
        }    
    }
}
void m_add_down_orders() {
    for (int i = 1; i<ORDER_SIZE; i++) {
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
            down_orders[i]=1;
            m_add_priority_orders(i);
        }
    }
}

void m_add_panel_orders() {
    for (int i = 0; i<ORDER_SIZE; i++) {
        if (elev_get_button_signal(BUTTON_COMMAND, i)) {
            panel_orders[i] = 1;
            m_add_priority_orders(i);
        }
        
    }
}

//receives a floor, checks if in list, adds if not.
void m_add_priority_orders(int floor) {
    assert(floor<4 &&floor >= 0);
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