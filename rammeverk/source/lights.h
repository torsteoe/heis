/**
 * @file
 * @brief A simple library for doing operations on lights
 * buffers consisting of integers
 */
 #ifndef LIGHTS_H__	/*include guard*/
#define LIGHTS_H__


#include "elev.h"
#include "queue.h"

/**
  Updates all lights except door lamp and stop lamp. 
*/
void lights_update_lights();



//hjelpefunksjoner

void set_floor_indicator_lights();
void set_order_indicator_lights();

#endif //#ifndef LIGHTS_H__