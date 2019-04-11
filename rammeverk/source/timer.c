/**
 * @file
 * @brief Implementation file for the timer module.
 */
#include "timer.h"
#include <time.h>

//////////////////////////////
////      VARIABLES       ////
//////////////////////////////

const double SECONDS = 3;
static clock_t clock_var; //Variable that will be used for storing clock ticks since program start.


//////////////////////////////
////      FUNCTIONS       ////
//////////////////////////////

void timer_start() {
    //set to current clock ticks since program started.
    clock_var = clock(); 
}
int timer_expired() {
    //make new variable containing ticks since program start.
    clock_t clock_now = clock();

    //compare with clock_var to know if three seconds have passed.
    return ((clock_now-clock_var)>=SECONDS*CLOCKS_PER_SEC); 
}