/**
 * @file
 * @brief A library for managing the state machine
 */
#ifndef FSM_H__	/*include guard*/
#define FSM_H__

#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "doors.h"

/**
  Initialize elevator.
*/
void FSM_init();

/**
  Perform action based on what state one is in. Change state if required.
*/
void FSM_changeState();

/**
  Initialize elevator.
  @return @c int ranging from @c 0 to @c 4 based on state.
*/
int FSM_get_state();



//hjelpefunksjoner

int ordered_to_same_floor();
int ordered_up();
int ordered_down();
int on_floor();
int orders_exist();

#endif //#ifndef FSM_H__