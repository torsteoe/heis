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

/**
  Delete orders at current floor.
*/
void queue_delete_floor_orders();

/**
  Iterate buttons and update orders accordingly.
*/
void queue_update_orders();

/**
  Print all orders in nice format in console.
*/
void queue_print_orders(); //just for debugging purposes

/**
  Set all order lists to default state.
*/
void queue_reset_orders();

/**
  Check if orders in direction that elevator will stop at. Safety measure.
  @param[in] direction -1 for down, 1 for up.
  @return @c 1 to signal orders exist, @c 0 to signal no orders.
*/
int queue_orders_in_direction(int direction); 


#endif //#ifndef QUEUE_H__
