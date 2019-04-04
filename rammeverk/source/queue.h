/**
 * @file
 * @brief A simple library for accessing queues and
 * doing operations on queue
 */
#ifndef QUEUE_H__   /*include guard*/
#define QUEUE_H__


#include "elev.h"
#include <stdio.h>
#include <assert.h>

/**
  Set previous floor equal to current floor.
*/
void queue_set_previous_floor();

/**
  Fetches previous floor.
  @return floor ranging from @c 0 to @c 3.
*/
int queue_get_previous_floor();

/**
  Fetches array of up-orders.
  @return array where each floor is represented by a 0 or 1, depending on, respectively, if
  there is an order or not.
*/
int * queue_get_up_orders();

/**
  Fetches array of down-orders.
  @return array where each floor is represented by a 0 or 1, depending on, respectively, if
  there is an order or not.
*/
int * queue_get_down_orders();

/**
  Fetches array of panel-orders (orders inside elevator).
  @return array where each floor is represented by a 0 or 1, depending on, respectively, if
  there is an order or not.
*/
int * queue_get_panel_orders();

/**
  Fetches priority order, first floor that was ordered that has still not been visited since order.
  @return floor ranging from @c 0 to @c 3.
*/
int queue_get_priority_order();


/**
  Check if elevator should stop at floor.
  @param[in] direction -1 for down, 1 for up, 2 to signal check in both directions
  @return @c 1 to signal stop, @c 0 to signal no stop
*/
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
