#include "elev.h"
#include <stdio.h>



void queue_set_previous_floor();
int queue_get_previous_floor();

int * queue_get_up_orders();
int * queue_get_down_orders();
int * queue_get_panel_orders();
int queue_get_priority_order();


int queue_should_I_stop_at_floor(int floor, int direction);
void queue_arrived_at_floor(int floor);
void queue_update_orders();
void queue_print_orders();
void queue_reset_orders();
void queue_init();




//hjelpefunksjoner
void add_up_orders();
void add_down_orders();
void add_panel_orders();
void add_priority_orders(int floor);

