#ifndef QUEUE_H__   /*include guard*/
#define QUEUE_H__


#include "elev.h"
#include <stdio.h>
#include <assert.h>


void queue_set_previous_floor();

int queue_get_previous_floor();

int * queue_get_up_orders();
int * queue_get_down_orders();
int * queue_get_panel_orders();
int queue_get_priority_order();


int queue_should_I_stop_at_floor(int direction);
void queue_delete_floor_orders();
void queue_update_orders();
void queue_print_orders(); //just for debugging purposes
void queue_reset_orders();
void queue_init();


int queue_orders_in_direction(int direction); //just for safety



//hjelpefunksjoner
void add_up_orders();
void add_down_orders();
void add_panel_orders();
void add_priority_orders(int floor);

#endif //#ifndef QUEUE_H__
