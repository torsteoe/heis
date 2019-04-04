/**
 * @file
 * @brief A simple library for doing operations with timer
 */
#ifndef TIMER_H__	/*include guard*/
#define TIMER_H__

#include <time.h>

/**
  Initialize timer: reset timer.
*/
void timer_init();

/**
  Reset timer.
*/
void timer_reset();

/**
  Check if timer is out.
  @return @c 1 if timer is out, @c 0 otherwise.
*/
int timer_is_timeout();

#endif //#ifndef TIMER_H__