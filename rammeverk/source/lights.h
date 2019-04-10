/**
 * @file
 * @brief A simple library for doing operations on lights.
 */
 #ifndef LIGHTS_H__	/*include guard*/
#define LIGHTS_H__


#include "elev.h"


/**
  Updates all lights except door lamp and stop lamp. 
  @param[in] previous_floor floor last visited or current floor if elevator on floor, used to set floor indicator lamp.
  @param[in, out] pp_orders pointer to dynamically allocated array containing all orders. Used to set button lights. Freed at end of function. 
*/
void lights_update_lights(int previous_floor, int ** pp_orders);





#endif //#ifndef LIGHTS_H__