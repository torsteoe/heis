/**
 * @file
 * @brief A simple library for doing operations with timer
 */
#ifndef TIMER_H__	/*include guard*/
#define TIMER_H__

#include <time.h>


/**
  Reset timer.
*/
void timer_start();

/**
  Check if timer is out.
  @return @c 1 if timer is out, @c 0 otherwise.
*/
int timer_expired();

#endif //#ifndef TIMER_H__