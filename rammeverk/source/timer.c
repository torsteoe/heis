/**
 * @file
 * @brief Implementation file for the timer module.
 */
#include "timer.h"
const double SECONDS = 3;
static clock_t clock_var;

void timer_start() {
    clock_var = clock();
}
int timer_expired() {
    clock_t clock_now = clock();
    return ((clock_now-clock_var)>=SECONDS*CLOCKS_PER_SEC); 
}