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
int FSM_init();

/**
  Perform action based on what state one is in. Change state if required.
*/
void FSM_update_state();

/**
  Initialize elevator.
  @return @c 0 to @c 4 based on current state.
*/
int FSM_get_state();




#endif //#ifndef FSM_H__