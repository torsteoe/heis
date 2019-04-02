
#ifndef FSM_H__	/*include guard*/
#define FSM_H__

#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "doors.h"


void FSM_init();
void FSM_changeState();
int FSM_get_state();



//hjelpefunksjoner
int ordered_up();
int ordered_down();
int on_floor();
int orders_exist();

#endif //#ifndef FSM_H__