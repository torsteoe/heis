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
  @return @c 1 on success, @c 0 if failed initiation.
*/
int FSM_init();

/**
  Perform action based on what state one is in. Change state if required.
*/
void FSM_update_state();





#endif //#ifndef FSM_H__