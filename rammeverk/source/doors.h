/**
 * @file
 * @brief A simple library for controlling the doors of the elevator
 * 
 */
#ifndef DOORS_H__	/*include guard*/
#define DOORS_H__


#include "elev.h"

void doors_change_state(int timeout);


//hjelpefunksjoner
void open_door();
void close_door();

#endif //#ifndef DOORS_H__