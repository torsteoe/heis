/**
 * @file
 * @brief Implementation file for the timer module.
 */
#include "timer.h"
const double SECONDS = 0.03; //change to three
static clock_t clock_var;

void timer_init() {
    timer_reset(); //changed from clock_var = clock();
}
void timer_reset() {
    clock_var = clock();
}
int timer_is_timeout() {
    clock_t clock_now = clock();
    return ((clock_now-clock_var)>=SECONDS*CLOCKS_PER_SEC); 
}