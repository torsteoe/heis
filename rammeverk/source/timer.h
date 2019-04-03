/**
 * @file
 * @brief A simple library for doing operations with timer
 */
#ifndef TIMER_H__	/*include guard*/
#define TIMER_H__

#include <time.h>

void timer_init();
void timer_reset();
int timer_is_timeout();

#endif //#ifndef TIMER_H__