/**
 * @file
 * @brief A simple library for doing operations on lights
 * buffers consisting of integers
 */
 #ifndef LIGHTS_H__	/*include guard*/
#define LIGHTS_H__


#include "elev.h"


/**
  Updates all lights except door lamp and stop lamp. 
*/
void lights_update_lights(int previous_floor, int ** pp_orders);





#endif //#ifndef LIGHTS_H__